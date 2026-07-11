#define WIN32_LEAN_AND_MEAN
#include <string>
#include <windows.h>

#include "jeode_native.h"
#include "ssl_hooks.h"

static const JeodeNativeAPI *g_api = nullptr;

static void clean_dat_files() {
  // Build path: %USERPROFILE%/AppData/LocalLow/Big Blue Bubble Inc/My Singing
  // Monsters/1/
  char profile[MAX_PATH];
  DWORD len = GetEnvironmentVariableA("USERPROFILE", profile, MAX_PATH);
  if (len == 0 || len >= MAX_PATH)
    return;

  std::string dir =
      std::string(profile) +
      "\\AppData\\LocalLow\\Big Blue Bubble Inc\\My Singing Monsters\\1";

  // Check directory exists
  DWORD attr = GetFileAttributesA(dir.c_str());
  if (attr == INVALID_FILE_ATTRIBUTES || !(attr & FILE_ATTRIBUTE_DIRECTORY))
    return;

  std::string pattern = dir + "\\*.dat";
  WIN32_FIND_DATAA fd;
  HANDLE hFind = FindFirstFileA(pattern.c_str(), &fd);
  if (hFind == INVALID_HANDLE_VALUE)
    return;

  int count = 0;
  do {
    if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      continue;
    std::string filepath = dir + "\\" + fd.cFileName;
    if (DeleteFileA(filepath.c_str()))
      count++;
  } while (FindNextFileA(hFind, &fd));
  FindClose(hFind);

  if (count > 0)
    g_log.info("Killed %d .dat file(s)\n", count);
}

extern "C" {

JEODE_EXPORT int JEODE_CALL
jeode_native_init(const struct JeodeNativeAPI *api) {
  if (!api || api->api_version < JEODE_NATIVE_API_VERSION)
    return -1;

  g_api = api;

  g_log.init(api->mod_path);
  g_log.good("========ROCKYHAXX========\n");
  g_log.info("Game version: %s\n", api->game_version);
  g_log.info("PID:          %lu\n", GetCurrentProcessId());

  clean_dat_files();

  if (!ssl_hook_install()) {
    g_log.err("WTF\n");
    return -1;
  }

  g_log.good("HACKING\n\n");

  return 0;
}

JEODE_EXPORT void JEODE_CALL jeode_native_shutdown(void) {
  ssl_hook_shutdown();
  g_log.good("\n==MR ROCKY SAYS BYE BYE==\n");
  g_log.shutdown();
}
}
