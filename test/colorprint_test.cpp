#include "../src/Colors.h"
#include "gtest/gtest.h"

using namespace peanut;

TEST(ColorPrint, Test1) {
  ColorPrintln(RED, "hello %s", "world");
  ColorPrintln(RED, "hello %s", "world");
  std::cout << "hello world\n";
  ColorPrintln(RED, "hello %s", "world");
  ColorPrintln(GREEN, "hello %s", "world");
  std::cout << "hello world\n";
  ColorPrintln(BLACK, "hello %s", "world");
  ColorPrintln(YELLOW, "hello %s", "world");
  ColorPrintln(BLUE, "hello %s", "world");
  ColorPrintln(PURPLE, "hello %s", "world");
  ColorPrintln(PURPLE, "hello %s", "world", " and colors");
}
