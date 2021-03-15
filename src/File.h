// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_FILE_H
#define PEANUT_BASE_FILE_H

#include <string>

namespace peanut {
namespace file {
const int FULLTEXT = 0;

std::string GetGBKFileContent(const std::string &filename, size_t len = FULLTEXT);
std::string GetUTF8FileContent(const std::string &filename, size_t len = FULLTEXT);
std::wstring GetUCS2FileContent(const std::string &filename, size_t len = FULLTEXT);
}  // namespace file

}  // namespace peanut

#endif  // #define PEANUT_BASE_FILE_H