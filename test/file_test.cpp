#include "../src/File.h"
#include <map>
#include "../src/Encoding.h"
#include "../src/StringUtil.h"
#include "fmt/color.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fmt::print(fg(fmt::color::red), "Usage: {} [gbk/utf8/ucs2] filename\n", argv[0]);
    return 1;
  }

  std::string encodingtype(argv[1]);
  if (peanut::Lower(encodingtype).compare("gbk") == 0)
    fmt::print(fg(fmt::color::green), "content:{}\n", peanut::file::GetGBKFileContent(argv[2]));
  else if (peanut::Lower(encodingtype).compare("utf8") == 0)
    fmt::print(fg(fmt::color::green), "content:{}\n", peanut::UTF8ToGBK(peanut::file::GetUTF8FileContent(argv[2])));
  else if (peanut::Lower(encodingtype).compare("ucs2") == 0)
    fmt::print(fg(fmt::color::green), "content:{}\n", peanut::UnicodeToGBK(peanut::file::GetUCS2FileContent(argv[2])));

  return 0;
}