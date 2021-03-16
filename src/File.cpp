#include "File.h"
#include <codecvt>
#include <fstream>
#include <locale>
#include "Encoding.h"

namespace peanut {
namespace detail {
void SkipUTF8BOM(std::ifstream &fin) {
  const char BOM[3] = {0xef, 0xbb, 0xbf};
  char file_head[3] = {0};
  fin.seekg(0, std::ios::beg);
  fin.read(file_head, 3);
  if (BOM[0] == file_head[0] && BOM[1] == file_head[1] && BOM[2] == file_head[2])
    return;
  else
    fin.seekg(0, std::ios::beg);
}
}  // namespace detail

namespace file {
std::string GetGBKFileContent(const std::string &filename, size_t len) {
  std::string content;
  std::ifstream fin(filename, std::ios::in | std::ios::binary);
  if (fin) {
    size_t content_len = len;
    if (FULLTEXT == len) {
      fin.seekg(0, std::ios::end);
      content_len = static_cast<size_t>(fin.tellg());
      fin.seekg(0, std::ios::beg);
    }
    content.resize(content_len);
    fin.read(&content[0], content.size());
    fin.close();
  }

  return content;
}

std::string GetUTF8FileContent(const std::string &filename, size_t len) {
  std::string content;
  std::ifstream fin(filename, std::ios::in | std::ios::binary);
  if (fin) {
    size_t content_len = len;
    if (FULLTEXT == len) {
      fin.seekg(0, std::ios::end);
      content_len = static_cast<size_t>(fin.tellg());
      fin.seekg(0, std::ios::beg);
    }
    detail::SkipUTF8BOM(fin);
    content.resize(content_len);
    fin.read(&content[0], content.size());
    fin.close();
  }

  return content;
}

std::wstring GetUCS2FileContent(const std::string &filename, size_t len) {
  std::wstring content;
  std::wfstream fin(filename, std::ios::in | std::ios::binary);
  if (fin) {
    size_t content_len = len;
    if (FULLTEXT == len) {
      fin.seekg(0, std::ios::end);
      content_len = static_cast<size_t>(fin.tellg());
      fin.seekg(0, std::ios::beg);
      content_len = (content_len - 2) / 2 + 1;
    }
    content.resize(content_len);

    fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));
    fin.read(&content[0], content.size());
    fin.close();
  }

  return content;
}
}  // namespace file
}  // namespace peanut