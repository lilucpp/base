// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_ATOMIC_H
#define PEANUT_BASE_ATOMIC_H

#include <stdint.h>
#include <atomic>
#include "Noncopyable.h"

namespace peanut {

namespace detail {
template <typename T>
class AtomicIntegerT : noncopyable {
 public:
  AtomicIntegerT() : value_(0) {}

  // uncomment if you need copying and assignment
  //
  // AtomicIntegerT(const AtomicIntegerT& that)
  //   : value_(that.get())
  // {}
  //
  // AtomicIntegerT& operator=(const AtomicIntegerT& that)
  // {
  //   getAndSet(that.get());
  //   return *this;
  // }

  T get() { return value_.load(); }

  T getAndAdd(T x) { return value_.fetch_add(x); }

  T addAndGet(T x) { return getAndAdd(x) + x; }

  T incrementAndGet() { return addAndGet(1); }

  T decrementAndGet() { return addAndGet(-1); }

  void add(T x) { getAndAdd(x); }

  void increment() { incrementAndGet(); }

  void decrement() { decrementAndGet(); }

  T getAndSet(T newValue) { return value_.exchange(newValue); }

 private:
  std::atomic<T> value_;
};
}  // namespace detail

typedef detail::AtomicIntegerT<int32_t> AtomicInt32;
typedef detail::AtomicIntegerT<int64_t> AtomicInt64;

}  // namespace peanut

#endif  // PEANUT_BASE_ATOMIC_H
