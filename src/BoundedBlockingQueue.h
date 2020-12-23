// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_BOUNDEDBLOCKINGQUEUE_H
#define PEANUT_BASE_BOUNDEDBLOCKINGQUEUE_H

#include "Condition.h"
#include "Mutex.h"

#include <assert.h>
#include <boost/circular_buffer.hpp>

namespace peanut {

template <typename T>
class BoundedBlockingQueue : noncopyable {
 public:
  explicit BoundedBlockingQueue(int maxSize) : mutex_(), notEmpty_(mutex_), notFull_(mutex_), queue_(maxSize) {}

  void put(const T &x) {
    MutexLockGuard lock(mutex_);
    while (queue_.full()) {
      notFull_.wait();
    }
    assert(!queue_.full());
    queue_.push_back(x);
    notEmpty_.notify();
  }

  T take() {
    MutexLockGuard lock(mutex_);
    while (queue_.empty()) {
      notEmpty_.wait();
    }
    assert(!queue_.empty());
    T front(queue_.front());
    queue_.pop_front();
    notFull_.notify();
    return front;
  }

  bool empty() const {
    MutexLockGuard lock(mutex_);
    return queue_.empty();
  }

  bool full() const {
    MutexLockGuard lock(mutex_);
    return queue_.full();
  }

  size_t size() const {
    MutexLockGuard lock(mutex_);
    return queue_.size();
  }

  size_t capacity() const {
    MutexLockGuard lock(mutex_);
    return queue_.capacity();
  }

 private:
  mutable MutexLock mutex_;
  Condition notEmpty_;
  Condition notFull_;
  boost::circular_buffer<T> queue_;
};

}  // namespace peanut

#endif  // PEANUT_BASE_BOUNDEDBLOCKINGQUEUE_H
