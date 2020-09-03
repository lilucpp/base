// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CONDITION_H
#define MUDUO_BASE_CONDITION_H

#include <condition_variable>

#include "Mutex.h"

namespace muduo {

class Condition : noncopyable {
 public:
  explicit Condition(MutexLock& mutex) : mutex_(mutex) {}

  ~Condition() {}

  void wait() {
    MutexLock::UnassignGuard ug(mutex_);
    pcond_.wait(mutex_.getMutex());
  }

  template <class Predicate>
  void wait(Predicate pred) {  // wait for signal and check predicate
    pcond_.wait(mutex_.getMutex(), pred);
  }

  // returns true if time out, false otherwise.
  bool waitForSeconds(double seconds);

  void notify() { pcond_.notify_one(); }

  void notifyAll() { pcond_.notify_all(); }

 private:
  MutexLock& mutex_;
  std::condition_variable_any pcond_;
};

}  // namespace muduo

#endif  // MUDUO_BASE_CONDITION_H
