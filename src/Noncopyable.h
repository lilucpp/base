// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_NONCOPYABLE_H
#define PEANUT_BASE_NONCOPYABLE_H

namespace peanut {

class noncopyable {
 public:
  noncopyable(const noncopyable &) = delete;
  void operator=(const noncopyable &) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

}  // namespace peanut

#endif  // PEANUT_BASE_NONCOPYABLE_H
