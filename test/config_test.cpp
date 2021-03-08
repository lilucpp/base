#include "../src/Config.h"
#include "../src/Application.h"
#include "gtest/gtest.h"

using namespace peanut;
TEST(ConfigTest, Test1) {
  std::string path = GetApplicationDir() + "/testdata/1.conf";
  Config conf(GetApplicationDir() + "/testdata/1.conf");
  std::string res;
  ASSERT_EQ("{key1:val1, key2:val2}", res << conf);
  res = conf.Get("key1", "");
  ASSERT_EQ("val1", res);
  res = conf.Get("key2", "");
  ASSERT_EQ("val2", res);
  const char *str = conf["key3"];
  ASSERT_FALSE(str);
  ASSERT_TRUE(0 == strcmp(conf["key2"], "val2"));
}
