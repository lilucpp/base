// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_EXCEPTION_H
#define PEANUT_BASE_EXCEPTION_H

#include <exception>

#include "Types.h"

namespace peanut {

class Exception : public std::exception {
 public:
  Exception(string what);
  ~Exception() noexcept override = default;

  // default copy-ctor and operator= are okay.

  const char *what() const noexcept override { return message_.c_str(); }

  const char *stackTrace() const noexcept { return stack_.c_str(); }

 private:
  string message_;
  string stack_;
};

}  // namespace peanut

#endif  // PEANUT_BASE_EXCEPTION_H
