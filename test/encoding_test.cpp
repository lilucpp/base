#include "../src/Encoding.h"
#include <codecvt>
#include <fstream>
#include <iostream>
#include "../src/Application.h"
#include "gtest/gtest.h"

using namespace peanut;
using namespace std;

TEST(EncodingTest, Test_GBKToUTF8) {
  string utf8, gbk;
  fstream u8ifs(GetApplicationDir() + "/testdata/dict.utf8", fstream::binary | fstream::in);
  fstream gbkifs(GetApplicationDir() + "/testdata/dict.gbk", fstream::binary | fstream::in);
  ASSERT_TRUE(u8ifs.is_open());
  ASSERT_TRUE(gbkifs.is_open());

  while (getline(u8ifs, utf8) && getline(gbkifs, gbk)) {
    ASSERT_EQ(GBKToUTF8(gbk), utf8);
  }
}

TEST(EncodingTest, Test_UTF8ToGBK) {
  string utf8, gbk;
  fstream u8ifs(GetApplicationDir() + "/testdata/dict.utf8", fstream::binary | fstream::in);
  fstream gbkifs(GetApplicationDir() + "/testdata/dict.gbk", fstream::binary | fstream::in);
  ASSERT_TRUE(u8ifs.is_open());
  ASSERT_TRUE(gbkifs.is_open());

  while (getline(u8ifs, utf8) && getline(gbkifs, gbk)) {
    ASSERT_EQ(gbk, UTF8ToGBK(utf8));
  }
}

TEST(EncodingTest, Test_GBKToUnicode) {
  string gbk;
  wstring unicode;
  wfstream unicodeifs(GetApplicationDir() + "/testdata/dict.unicode", fstream::binary | wfstream::in);
  fstream gbkifs(GetApplicationDir() + "/testdata/dict.gbk", fstream::binary | fstream::in);
  ASSERT_TRUE(unicodeifs.is_open());
  ASSERT_TRUE(gbkifs.is_open());
  unicodeifs.imbue(std::locale(unicodeifs.getloc(), new std::codecvt_utf16<wchar_t, 0xffff, std::consume_header>));

  while (getline(unicodeifs, unicode) && getline(gbkifs, gbk)) {
    ASSERT_EQ(GBKToUnicode(gbk), unicode);
  }
}

TEST(EncodingTest, Test_UnicodeToGBK) {
  string gbk;
  wstring unicode;
  wfstream unicodeifs(GetApplicationDir() + "/testdata/dict.unicode", fstream::binary | fstream::in);
  fstream gbkifs(GetApplicationDir() + "/testdata/dict.gbk", fstream::binary | fstream::in);
  ASSERT_TRUE(unicodeifs.is_open());
  ASSERT_TRUE(gbkifs.is_open());
  unicodeifs.imbue(std::locale(unicodeifs.getloc(), new std::codecvt_utf16<wchar_t, 0xffff, std::consume_header>));

  while (getline(unicodeifs, unicode) && getline(gbkifs, gbk)) {
    ASSERT_EQ(gbk, UnicodeToGBK(unicode));
  }
}

TEST(EncodingTest, Test_UTF8ToUnicode) {
  string utf8;
  wstring unicode;
  fstream u8ifs(GetApplicationDir() + "/testdata/dict.utf8", fstream::binary | fstream::in);
  wfstream unicodeifs(GetApplicationDir() + "/testdata/dict.unicode", fstream::binary | fstream::in);
  ASSERT_TRUE(unicodeifs.is_open());
  ASSERT_TRUE(u8ifs.is_open());
  unicodeifs.imbue(std::locale(unicodeifs.getloc(), new std::codecvt_utf16<wchar_t, 0xffff, std::consume_header>));

  while (getline(u8ifs, utf8) && getline(unicodeifs, unicode)) {
    ASSERT_EQ(UTF8ToUnicode(utf8), unicode);
  }
}

TEST(EncodingTest, Test_UnicodeToUtf8) {
  string utf8;
  wstring unicode;
  fstream u8ifs(GetApplicationDir() + "/testdata/dict.utf8", fstream::binary | fstream::in);
  wfstream unicodeifs(GetApplicationDir() + "/testdata/dict.unicode", fstream::binary | fstream::in);
  ASSERT_TRUE(unicodeifs.is_open());
  ASSERT_TRUE(u8ifs.is_open());
  unicodeifs.imbue(std::locale(unicodeifs.getloc(), new std::codecvt_utf16<wchar_t, 0xffff, std::consume_header>));

  while (getline(u8ifs, utf8) && getline(unicodeifs, unicode)) {
    ASSERT_EQ(utf8, UnicodeToUtf8(unicode));
  }
}