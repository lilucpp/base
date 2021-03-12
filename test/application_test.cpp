#include "../src/Application.h"
#include <map>
#include "../src/Encoding.h"
#include "fmt/color.h"

int main() {
  using namespace peanut;

  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), "application path={}\n", GetApplicationPath());
  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), L"application pathW={}\n", GetApplicationPathW());

  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), "application dir={}\n", GetApplicationDir());
  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), L"application dirW={}\n", GetApplicationDirW());

  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), "temp dir={}\n", GetTempDir());
  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), L"temp dirW={}\n", GetTempDirW());

  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), "temp file path={}\n", GetUniquePath());
  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), L"temp file pathW={}\n", GetUniquePathW());

  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), "temp file path with prefix={}\n",
             GetUniquePath("superred_"));
  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), L"temp file pathW with prefix={}\n",
             GetUniquePathW(L"superred_"));

  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), "temp file path with suffix={}\n",
             GetUniquePath("", ".txt"));
  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), L"temp file pathW with suffix={}\n",
             GetUniquePathW(L"", L".txt"));

  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), "temp file path with pre/suffix ={}\n",
             GetUniquePath("superred_", ".txt"));
  fmt::print(fg(fmt::color::purple) | bg(fmt::color::cyan), L"temp file pathW with pre/suffix ={}\n",
             GetUniquePathW(L"superred_", L".txt"));

  std::map<std::string, int> c;
  for (int i = 0; i < 100000; ++i) ++c[GetUniquePath()];

  fmt::print("The container size is {} after inserting 100,000 paths.\n", c.size());
  bool isRepeat = false;
  std::map<std::string, int>::const_iterator itr;
  for (itr = c.begin(); itr != c.end(); ++itr) {
    if (itr->second > 1) {
      fmt::print("  repeat name:{}={}\n", itr->first, itr->second);
      isRepeat = true;
    }
  }
  if (!isRepeat) fmt::print("There is no duplicate path name in the container.\n");

  return 0;
}
