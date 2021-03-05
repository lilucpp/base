#include "../src/Encoding.h"
#include "../src/Application.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <codecvt>

using namespace peanut;
using namespace std;

TEST(EncodingTest, Test_gbktoutf8) {
  string utf8, gbk;
  fstream u8ifs(GetApplicationDir() + "/testdata/dict.utf8", fstream::binary | fstream::in);
  fstream gbkifs("./testdata/dict.gbk", fstream::binary | fstream::in);
  ASSERT_TRUE(u8ifs.is_open());
  ASSERT_TRUE(gbkifs.is_open());

  while (getline(u8ifs, utf8) && getline(gbkifs, gbk)) {
    ASSERT_EQ(gbktoutf8(gbk), utf8);
  }
}

TEST(EncodingTest, Test_utf8togbk) {
  string utf8, gbk;
  fstream u8ifs(GetApplicationDir() + "/testdata/dict.utf8", fstream::binary | fstream::in);
  fstream gbkifs(GetApplicationDir() + "/testdata/dict.gbk", fstream::binary | fstream::in);
  ASSERT_TRUE(u8ifs.is_open());
  ASSERT_TRUE(gbkifs.is_open());

  while (getline(u8ifs, utf8) && getline(gbkifs, gbk)) {
    ASSERT_EQ(gbk, utf8togbk(utf8));
  }
}

TEST(EncodingTest, Test_gbktounicode) {
  string gbk;
  wstring unicode;
  wfstream unicodeifs(GetApplicationDir() + "/testdata/dict.unicode", fstream::binary | wfstream::in);
  fstream gbkifs(GetApplicationDir() + "/testdata/dict.gbk", fstream::binary | fstream::in);
  ASSERT_TRUE(unicodeifs.is_open());
  ASSERT_TRUE(gbkifs.is_open());
  unicodeifs.imbue(std::locale(unicodeifs.getloc(), new std::codecvt_utf16<wchar_t, 0xffff, std::consume_header>));

  while (getline(unicodeifs, unicode) && getline(gbkifs, gbk)) {
    ASSERT_EQ(gbktounicode(gbk), unicode);
  }
}

TEST(EncodingTest, Test_unicodetogbk) {
  string gbk;
  wstring unicode;
  wfstream unicodeifs(GetApplicationDir() + "/testdata/dict.unicode", fstream::binary | fstream::in);
  fstream gbkifs(GetApplicationDir() + "/testdata/dict.gbk", fstream::binary | fstream::in);
  ASSERT_TRUE(unicodeifs.is_open());
  ASSERT_TRUE(gbkifs.is_open());
  unicodeifs.imbue(std::locale(unicodeifs.getloc(), new std::codecvt_utf16<wchar_t, 0xffff, std::consume_header>));

  while (getline(unicodeifs, unicode) && getline(gbkifs, gbk)) {
    ASSERT_EQ(gbk, unicodetogbk(unicode));
  }
}

TEST(EncodingTest, Test_utf8tounicode) {
  string utf8;
  wstring unicode;
  fstream u8ifs(GetApplicationDir() + "/testdata/dict.utf8", fstream::binary | fstream::in);
  wfstream unicodeifs(GetApplicationDir() + "/testdata/dict.unicode", fstream::binary | fstream::in);
  ASSERT_TRUE(unicodeifs.is_open());
  ASSERT_TRUE(u8ifs.is_open());
  unicodeifs.imbue(std::locale(unicodeifs.getloc(), new std::codecvt_utf16<wchar_t, 0xffff, std::consume_header>));

  while(getline(u8ifs, utf8) && getline(unicodeifs, unicode)) {
      ASSERT_EQ(utf8tounicode(utf8), unicode);
  }
}

TEST(EncodingTest, Test_unicodetoutf8) {
  string utf8;
  wstring unicode;
  fstream u8ifs(GetApplicationDir() + "/testdata/dict.utf8", fstream::binary | fstream::in);
  wfstream unicodeifs(GetApplicationDir() + "/testdata/dict.unicode", fstream::binary | fstream::in);
  ASSERT_TRUE(unicodeifs.is_open());
  ASSERT_TRUE(u8ifs.is_open());
  unicodeifs.imbue(std::locale(unicodeifs.getloc(), new std::codecvt_utf16<wchar_t, 0xffff, std::consume_header>));

  while(getline(u8ifs, utf8) && getline(unicodeifs, unicode)) {
      ASSERT_EQ(utf8, unicodetoutf8(unicode));
  }
}