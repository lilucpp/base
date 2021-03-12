// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_CONFIG_H
#define PEANUT_BASE_CONFIG_H

#include <assert.h>
#include <fstream>
#include <iostream>
#include <map>
#include "StringUtil.h"

namespace peanut {

class Config {
 public:
  explicit Config(const std::string &filePath) { LoadFile(filePath); }

  operator bool() { return !map_.empty(); }

  std::string Get(const std::string &key, const std::string &defaultvalue) const {
    std::map<std::string, std::string>::const_iterator it = map_.find(key);
    if (map_.end() != it) {
      return it->second;
    }
    return defaultvalue;
  }
  int Get(const std::string &key, int defaultvalue) const {
    std::string str = Get(key, "");
    if ("" == str) {
      return defaultvalue;
    }
    return atoi(str.c_str());
  }
  const char *operator[](const char *key) const {
    if (NULL == key) {
      return NULL;
    }
    std::map<std::string, std::string>::const_iterator it = map_.find(key);
    if (map_.end() != it) {
      return it->second.c_str();
    }
    return NULL;
  }

  std::string GetConfigInfo() const {
    std::string res;
    res << *this;
    return res;
  }

 private:
  void LoadFile(const std::string &filePath) {
    std::ifstream ifs(filePath.c_str());
    assert(ifs);
    std::string line;
    std::vector<std::string> vecBuf;
    size_t lineno = 0;
    while (getline(ifs, line)) {
      lineno++;
      Trim(line);
      if (line.empty() || StartsWith(line, "#")) {
        continue;
      }
      vecBuf.clear();
      Split(line, vecBuf, "=");
      if (2 != vecBuf.size()) {
        fprintf(stderr, "line[%s] illegal.\n", line.c_str());
        assert(false);
        continue;
      }
      std::string &key = vecBuf[0];
      std::string &value = vecBuf[1];
      Trim(key);
      Trim(value);
      if (!map_.insert(make_pair(key, value)).second) {
        fprintf(stderr, "key[%s] already exits.\n", key.c_str());
        assert(false);
        continue;
      }
    }
    ifs.close();
  }

  friend std::ostream &operator<<(std::ostream &os, const Config &config);

  std::map<std::string, std::string> map_;
};  // class Config

inline std::ostream &operator<<(std::ostream &os, const Config &config) { return os << config.map_; }

}  // namespace peanut

#endif  // PEANUT_BASE_CONFIG_H
