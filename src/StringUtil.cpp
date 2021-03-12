#include "StringUtil.h"
#include <random>

namespace peanut {

std::string &Upper(std::string &str) {
  transform(str.begin(), str.end(), str.begin(), ::toupper);
  return str;
}

std::string &Lower(std::string &str) {
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

std::string &LTrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
  return s;
}

std::string &RTrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
  return s;
}

bool IsSpace(unsigned c) {
  // when passing large int as the argument of isspace, it core dump, so here
  // need a type cast.
  return c > 0xff ? false : std::isspace(c & 0xff) != 0;
}

std::string &Trim(std::string &s) { return LTrim(RTrim(s)); }

void Split(const std::string &src, std::vector<std::string> &res, const std::string &pattern, size_t maxsplit) {
  res.clear();
  size_t Start = 0;
  size_t end = 0;
  std::string sub;
  while (Start < src.size()) {
    end = src.find_first_of(pattern, Start);
    if (std::string::npos == end || res.size() >= maxsplit) {
      sub = src.substr(Start);
      res.push_back(sub);
      return;
    }
    sub = src.substr(Start, end - Start);
    res.push_back(sub);
    Start = end + 1;
  }
  return;
}

std::vector<std::string> Split(const std::string &src, const std::string &pattern, size_t maxsplit) {
  std::vector<std::string> res;
  Split(src, res, pattern, maxsplit);
  return res;
}

bool StartsWith(const std::string &str, const std::string &prefix) {
  if (prefix.length() > str.length()) {
    return false;
  }
  return 0 == str.compare(0, prefix.length(), prefix);
}

bool EndsWith(const std::string &str, const std::string &suffix) {
  if (suffix.length() > str.length()) {
    return false;
  }
  return 0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix);
}

/*
 * format example: "%Y-%m-%d %H:%M:%S"
 */
void GetTime(const std::string &format, std::string &timeStr) {
  time_t timeNow;
  time(&timeNow);
  timeStr.resize(64);
  tm tm_now;
#if defined _WIN32
  localtime_s(&tm_now, &timeNow);
#else
  localtime_r(&timeNow, &tm_now);
#endif  // _WIN32
  size_t len = strftime(&timeStr[0], timeStr.size(), format.c_str(), &tm_now);
  timeStr.resize(len);
}

std::string PathJoin(const std::string &path1, const std::string &path2) {
  if (EndsWith(path1, "/")) {
    return path1 + path2;
  }
  return path1 + "/" + path2;
}

std::string GenRandomString(const int len) {
  std::mt19937 generator{std::random_device{}()};
  // modify range according to your need "A-Z","a-z" or "0-9" or whatever you need.
  std::uniform_int_distribution<int> distribution{'a', 'z'};
  std::string rand_str(len, '\0');
  for (auto &dis : rand_str) dis = static_cast<char>(distribution(generator));

  return rand_str;
}

}  // namespace peanut