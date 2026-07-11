#pragma once
#define WIN32_LEAN_AND_MEAN
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <windows.h>

class Logger {
  HANDLE hConsole_ = nullptr;
  FILE *logFile_ = nullptr;
  std::mutex mtx_;

public:
  void init(const char *mod_path) {
    std::lock_guard<std::mutex> lock(mtx_);

    if (!GetConsoleWindow())
      AllocConsole();
    hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);

    HWND con = GetConsoleWindow();
    if (con) {
      ShowWindow(con, SW_SHOW);
      SetConsoleTitleA("ROCKYHAXX");
    }

    if (mod_path) {
      std::string path = std::string(mod_path) + "\\rockyhaxx.txt";
      logFile_ = fopen(path.c_str(), "w");
    }
  }

  void shutdown() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (logFile_) {
      fclose(logFile_);
      logFile_ = nullptr;
    }
  }

  void write(WORD color, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    write_impl(color, fmt, args);
    va_end(args);
  }

  void info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    write_impl(0x07, fmt, args);
    va_end(args);
  }

  void good(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    write_impl(0x0A, fmt, args);
    va_end(args);
  }

  void warn(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    write_impl(0x0E, fmt, args);
    va_end(args);
  }

  void err(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    write_impl(0x0C, fmt, args);
    va_end(args);
  }

  void hex_dump(const void *data, size_t len) {
    const auto *p = static_cast<const uint8_t *>(data);
    for (size_t off = 0; off < len; off += 16) {
      char line[80];
      int pos = snprintf(line, sizeof(line), "  %04zx  ", off);
      for (int i = 0; i < 16; i++) {
        if (off + i < len)
          pos += snprintf(line + pos, sizeof(line) - pos, "%02x ", p[off + i]);
        else
          pos += snprintf(line + pos, sizeof(line) - pos, "   ");
        if (i == 7)
          line[pos++] = ' ';
      }
      pos += snprintf(line + pos, sizeof(line) - pos, " |");
      for (int i = 0; i < 16 && off + i < len; i++) {
        uint8_t c = p[off + i];
        line[pos++] = (c >= 0x20 && c < 0x7F) ? c : '.';
      }
      line[pos++] = '|';
      line[pos++] = '\n';
      line[pos] = '\0';
      write(0x08, "%s", line);
    }
  }

private:
  void write_impl(WORD color, const char *fmt, va_list args) {
    std::lock_guard<std::mutex> lock(mtx_);

    // Measure required size
    va_list args_copy;
    va_copy(args_copy, args);
    int n = vsnprintf(nullptr, 0, fmt, args_copy);
    va_end(args_copy);
    if (n <= 0)
      return;

    // Allocate exact buffer stack=small heap=large
    char stack_buf[512];
    char *buf =
        (n < (int)sizeof(stack_buf)) ? stack_buf : (char *)malloc(n + 1);
    if (!buf)
      return;

    vsnprintf(buf, n + 1, fmt, args);

    if (hConsole_) {
      SetConsoleTextAttribute(hConsole_, color);
      DWORD written;
      WriteConsoleA(hConsole_, buf, n, &written, nullptr);
      SetConsoleTextAttribute(hConsole_, 0x07);
    }
    if (logFile_) {
      fwrite(buf, 1, n, logFile_);
      fflush(logFile_);
    }

    if (buf != stack_buf)
      free(buf);
  }
};

inline Logger g_log;
