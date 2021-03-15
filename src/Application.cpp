#include "Application.h"
#include "Encoding.h"
#include "boost/filesystem.hpp"
#include "boost/system/error_code.hpp"

namespace peanut {
// https://stackoverflow.com/a/55579815/8330816
std::string GetApplicationPath() {
#ifdef _WIN32
  char path[MAX_PATH] = {0};
  GetModuleFileNameA(NULL, path, MAX_PATH);
  return path;
#else
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  return std::string(result, (count > 0) ? count : 0);
#endif
}

std::wstring GetApplicationPathW() {
#ifdef _WIN32
  return GBKToUnicode(GetApplicationPath());
#else
  return UTF8ToUnicode(GetApplicationPath());
#endif
}

std::string GetApplicationDir() {
  std::string path = GetApplicationPath();
  std::string::size_type pos = path.find_last_of("\\/");
  if (std::string::npos != pos) return path.substr(0, pos);

  return ".";
}

std::wstring GetApplicationDirW() {
#ifdef _WIN32
  return GBKToUnicode(GetApplicationDir());
#else
  return UTF8ToUnicode(GetApplicationDir());
#endif
}

std::string GetTempDir() {
  boost::filesystem::path temp = boost::filesystem::temp_directory_path();

  return temp.string();
}

std::wstring GetTempDirW() {
  boost::filesystem::path temp = boost::filesystem::temp_directory_path();

  return temp.wstring();
}

std::string GetUniquePath(const std::string &prefix, const std::string &suffix) {
  boost::filesystem::path temp = boost::filesystem::temp_directory_path();
  temp += boost::filesystem::path::preferred_separator;
  temp += boost::filesystem::unique_path(prefix + "%%%%-%%%%-%%%%-%%%%");
  if (suffix.empty()) return temp.string();

  return temp.string() + suffix;
}

std::wstring GetUniquePathW(const std::wstring &prefix, const std::wstring &suffix) {
  boost::filesystem::path temp = boost::filesystem::temp_directory_path();
  temp += boost::filesystem::path::preferred_separator;
  temp += boost::filesystem::unique_path(prefix + L"%%%%-%%%%-%%%%-%%%%");

  if (suffix.empty()) return temp.wstring();

  return temp.wstring() + suffix;
}

bool CreateDirectories(const std::string &path) {
  boost::system::error_code ec;
  return boost::filesystem::create_directories(path, ec);
}

bool CreateDirectories(const std::wstring &path) {
  boost::system::error_code ec;
  return boost::filesystem::create_directories(path, ec);
}

}  // namespace peanut