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
#include "fmt/printf.h"

namespace peanut {

#ifdef _WIN32
#pragma warning(disable : 4505)
#endif // _WIN32

template <typename S, typename... Args>
inline std::string StringFormat(const S &format_str, const Args &... args) {
  return fmt::sprintf(format_str, args...);
}

template <class T>
void Join(T begin, T end, std::string &res, const std::string &connector) {
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
std::string Join(T begin, T end, const std::string &connector) {
  std::string res;
  Join(begin, end, res, connector);
  return res;
}

std::string &Upper(std::string &str);
std::string &Lower(std::string &str);

bool IsSpace(unsigned c);

std::string &LTrim(std::string &s);
std::string &RTrim(std::string &s);
std::string &Trim(std::string &s);

void Split(const std::string &src, std::vector<std::string> &res, const std::string &pattern,
           size_t maxsplit = std::string::npos);
std::vector<std::string> Split(const std::string &src, const std::string &pattern, size_t maxsplit = std::string::npos);

bool StartsWith(const std::string &str, const std::string &prefix);
bool EndsWith(const std::string &str, const std::string &suffix);

inline bool IsInStr(const std::string &str, char ch) { return str.find(ch) != std::string::npos; }

/*
 * format example: "%Y-%m-%d %H:%M:%S"
 */
void GetTime(const std::string &format, std::string &timeStr);

std::string PathJoin(const std::string &path1, const std::string &path2);
std::string GenRandomString(const int len);

}  // namespace peanut
#endif  // PEANUT_BASE_STRINGUTIL_H
