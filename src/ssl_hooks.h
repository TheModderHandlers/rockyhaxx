#pragma once
#define WIN32_LEAN_AND_MEAN
#include <MinHook.h>
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <windows.h>

#include "logger.h"
#include "sfs_dumper.h"
#include "ws_parser.h"

typedef int(__cdecl *SSL_read_t)(void *ssl, void *buf, int num);
typedef int(__cdecl *SSL_write_t)(void *ssl, const void *buf, int num);

static SSL_read_t g_orig_SSL_read = nullptr;
static SSL_write_t g_orig_SSL_write = nullptr;
static void *g_pSSL_read = nullptr;
static void *g_pSSL_write = nullptr;

static std::unordered_map<void *, WsParser> g_read_parsers;
static std::unordered_map<void *, WsParser> g_write_parsers;
static std::mutex g_parser_mtx;

struct DumpJob {
  std::string direction;
  std::vector<uint8_t> payload;
};

static std::queue<DumpJob> g_dump_queue;
static std::mutex g_dump_mtx;
static std::condition_variable g_dump_cv;
static std::atomic<bool> g_dump_running{false};
static std::thread g_dump_thread;

static void dump_thread_func() {
  while (g_dump_running) {
    std::unique_lock<std::mutex> lock(g_dump_mtx);
    g_dump_cv.wait(lock,
                   [] { return !g_dump_queue.empty() || !g_dump_running; });
    while (!g_dump_queue.empty()) {
      DumpJob job = std::move(g_dump_queue.front());
      g_dump_queue.pop();
      lock.unlock();
      g_dumper.dump_packet(job.direction.c_str(), job.payload.data(),
                           job.payload.size());
      lock.lock();
    }
  }
}

static void enqueue_dump(const char *direction, const uint8_t *data,
                         size_t len) {

  std::lock_guard<std::mutex> lock(g_dump_mtx);
  g_dump_queue.push({direction, std::vector<uint8_t>(data, data + len)});
  g_dump_cv.notify_one();
}

// ws callbacks
static void on_ws_recv(const WsMessage &msg) {
  if (msg.opcode == WS_BINARY && !msg.payload.empty())
    enqueue_dump("RECV", msg.payload.data(), msg.payload.size());
}

static void on_ws_send(const WsMessage &msg) {
  if (msg.opcode == WS_BINARY && !msg.payload.empty())
    enqueue_dump("SEND", msg.payload.data(), msg.payload.size());
}

// ssl stuff
static int __cdecl hooked_SSL_read(void *ssl, void *buf, int num) {
  int ret = g_orig_SSL_read(ssl, buf, num);
  if (ret > 0) {
    std::lock_guard<std::mutex> lock(g_parser_mtx);
    g_read_parsers[ssl].feed(reinterpret_cast<const uint8_t *>(buf), ret,
                             on_ws_recv);
  }
  return ret;
}

static int __cdecl hooked_SSL_write(void *ssl, const void *buf, int num) {
  if (num > 0) {
    std::lock_guard<std::mutex> lock(g_parser_mtx);
    g_write_parsers[ssl].feed(reinterpret_cast<const uint8_t *>(buf), num,
                              on_ws_send);
  }
  return g_orig_SSL_write(ssl, buf, num);
}

// hookin
static bool install_hook(void *target, void *detour, void **original,
                         const char *name) {
  if (!target) {
    g_log.warn("%s: not found\n", name);
    return false;
  }
  MH_STATUS s = MH_CreateHook(target, detour, original);
  if (s != MH_OK) {
    g_log.err("MH_CreateHook(%s): %d\n", name, s);
    return false;
  }
  s = MH_EnableHook(target);
  if (s != MH_OK) {
    g_log.err("MH_EnableHook(%s): %d\n", name, s);
    return false;
  }
  return true;
}

static bool ssl_hook_install() {
  MH_STATUS init_st = MH_Initialize();
  if (init_st != MH_OK && init_st != MH_ERROR_ALREADY_INITIALIZED) {
    g_log.err("MH_Initialize failed: %d\n", init_st);
    return false;
  }
  HMODULE hSSL = GetModuleHandleA("libssl-3.dll");
  if (!hSSL) {
    hSSL = LoadLibraryA("libssl-3.dll");
    if (!hSSL) {
      g_log.err("libssl-3.dll not found\n");
      return false;
    }
  }
  g_log.good("libssl-3.dll at 0x%p\n", hSSL);
  g_pSSL_read = reinterpret_cast<void *>(GetProcAddress(hSSL, "SSL_read"));
  g_pSSL_write = reinterpret_cast<void *>(GetProcAddress(hSSL, "SSL_write"));
  g_log.info("SSL_read @ 0x%p, SSL_write @ 0x%p\n", g_pSSL_read, g_pSSL_write);

  g_dump_running = true;
  g_dump_thread = std::thread(dump_thread_func);

  bool ok = true;
  if (g_pSSL_read)
    ok &= install_hook(g_pSSL_read, reinterpret_cast<void *>(&hooked_SSL_read),
                       reinterpret_cast<void **>(&g_orig_SSL_read), "SSL_read");
  if (g_pSSL_write)
    ok &=
        install_hook(g_pSSL_write, reinterpret_cast<void *>(&hooked_SSL_write),
                     reinterpret_cast<void **>(&g_orig_SSL_write), "SSL_write");
  if (ok)
    g_log.good("installed rockyhaxx\n");
  return ok;
}

static void ssl_hook_shutdown() {
  if (g_pSSL_read)
    MH_DisableHook(g_pSSL_read);
  if (g_pSSL_write)
    MH_DisableHook(g_pSSL_write);
  MH_Uninitialize();
  g_dump_running = false;
  g_dump_cv.notify_one();
  if (g_dump_thread.joinable())
    g_dump_thread.join();
  std::lock_guard<std::mutex> lock(g_parser_mtx);
  g_read_parsers.clear();
  g_write_parsers.clear();
}
