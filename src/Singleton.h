// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_SINGLETON_H
#define PEANUT_BASE_SINGLETON_H

#include "Noncopyable.h"

#include <assert.h>
#include <stdlib.h>  // atexit
#include <mutex>

namespace peanut {

namespace detail {
// This doesn't detect inherited member functions!
// http://stackoverflow.com/questions/1966362/sfinae-to-check-for-inherited-member-functions
template <typename T>
struct has_no_destroy {
  template <typename C>
  static char test(decltype(&C::no_destroy));
  template <typename C>
  static int32_t test(...);
  const static bool value = sizeof(test<T>(0)) == 1;
};
}  // namespace detail

template <typename T>
class Singleton : noncopyable {
 public:
  Singleton() = delete;
  ~Singleton() = delete;

  static T &instance() {
    std::call_once(ponce_, &Singleton::init);
    assert(value_ != NULL);
    return *value_;
  }

 private:
  static void init() {
    value_ = new T();
    if (!detail::has_no_destroy<T>::value) {
      ::atexit(destroy);
    }
  }

  static void destroy() {
    typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    T_must_be_complete_type dummy;
    (void)dummy;

    delete value_;
    value_ = NULL;
  }

 private:
  static std::once_flag ponce_;
  static T *value_;
};

template <typename T>
std::once_flag Singleton<T>::ponce_;

template <typename T>
T *Singleton<T>::value_ = NULL;

}  // namespace peanut

#endif  // PEANUT_BASE_SINGLETON_H
