// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_MUTEX_H
#define PEANUT_BASE_MUTEX_H

#include <assert.h>
#include <mutex>
#include "CurrentThread.h"
#include "Noncopyable.h"

namespace peanut {

class MutexLock : noncopyable {
 public:
  MutexLock() : holder_(0) {}

  ~MutexLock() { assert(holder_ == 0); }

  // must be called when locked, i.e. for assertion
  bool isLockedByThisThread() const { return holder_ == CurrentThread::tid(); }

  void assertLocked() const { assert(isLockedByThisThread()); }

  // internal usage

  void lock() {
    mutex_.lock();
    assignHolder();
  }

  void unlock() {
    unassignHolder();
    mutex_.unlock();
  }

  std::mutex &getMutex() /* non-const */
  {
    return mutex_;
  }

 private:
  friend class Condition;

  class UnassignGuard : noncopyable {
   public:
    explicit UnassignGuard(MutexLock &owner) : owner_(owner) { owner_.unassignHolder(); }

    ~UnassignGuard() { owner_.assignHolder(); }

   private:
    MutexLock &owner_;
  };

  void unassignHolder() { holder_ = 0; }

  void assignHolder() { holder_ = CurrentThread::tid(); }

  std::mutex mutex_;
  pid_t holder_;
};

// Use as a stack variable, eg.
// int Foo::size() const
// {
//   MutexLockGuard lock(mutex_);
//   return data_.size();
// }
class MutexLockGuard : noncopyable {
 public:
  explicit MutexLockGuard(MutexLock &mutex) : mutex_(mutex) { mutex_.lock(); }

  ~MutexLockGuard() { mutex_.unlock(); }

 private:
  MutexLock &mutex_;
};

}  // namespace peanut

// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!
#define MutexLockGuard(x) error "Missing guard object name"

#endif  // PEANUT_BASE_MUTEX_H
