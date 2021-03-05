// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_STRINGUTIL_H
#define PEANUT_BASE_STRINGUTIL_H
#include <memory.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "StdExtension.h"

namespace peanut {

inline std::string StringFormat(const char *fmt, ...) {
  int size = 256;
  std::string str;
  va_list ap;
  while (1) {
    str.resize(size);
    va_start(ap, fmt);
    int n = vsnprintf(&str[0], size, fmt, ap);
    va_end(ap);
    if (n > -1 && n < size) {
      str.resize(n);
      return str;
    }
    if (n > -1)
      size = n + 1;
    else
      size *= 2;
  }
  return str;
}

template <class T>
void join(T begin, T end, std::string &res, const std::string &connector) {
  if (begin == end) {
    return;
  }
  std::stringstream ss;
  ss << *begin;
  ++begin;
  while (begin != end) {
    ss << connector << *begin;
    ++begin;
  }
  res = ss.str();
}

template <class T>
std::string join(T begin, T end, const std::string &connector) {
  std::string res;
  join(begin, end, res, connector);
  return res;
}

inline std::string &upper(std::string &str) {
  transform(str.begin(), str.end(), str.begin(), ::toupper);
  return str;
}

inline std::string &lower(std::string &str) {
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

inline bool IsSpace(unsigned c) {
  // when passing large int as the argument of isspace, it core dump, so here
  // need a type cast.
  return c > 0xff ? false : std::isspace(c & 0xff) != 0;
}

inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
  return s;
}

inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
  return s;
}

inline std::string &trim(std::string &s) { return ltrim(rtrim(s)); }

inline void split(const std::string &src, std::vector<std::string> &res, const std::string &pattern,
                  size_t maxsplit = std::string::npos) {
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

inline std::vector<std::string> split(const std::string &src, const std::string &pattern,
                                      size_t maxsplit = std::string::npos) {
  std::vector<std::string> res;
  split(src, res, pattern, maxsplit);
  return res;
}

inline bool startsWith(const std::string &str, const std::string &prefix) {
  if (prefix.length() > str.length()) {
    return false;
  }
  return 0 == str.compare(0, prefix.length(), prefix);
}

inline bool endsWith(const std::string &str, const std::string &suffix) {
  if (suffix.length() > str.length()) {
    return false;
  }
  return 0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix);
}

inline bool IsInStr(const std::string &str, char ch) { return str.find(ch) != std::string::npos; }

/*
 * format example: "%Y-%m-%d %H:%M:%S"
 */
inline void GetTime(const std::string &format, std::string &timeStr) {
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

inline std::string pathJoin(const std::string &path1, const std::string &path2) {
  if (endsWith(path1, "/")) {
    return path1 + path2;
  }
  return path1 + "/" + path2;
}

}  // namespace peanut
#endif  // PEANUT_BASE_STRINGUTIL_H
