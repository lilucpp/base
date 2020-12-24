// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_THREAD_H
#define PEANUT_BASE_THREAD_H

#include <functional>
#include <memory>
#include <thread>

#include "Atomic.h"
#include "CountDownLatch.h"
#include "Types.h"

#if defined _WIN32
#define pthread_t size_t
#endif  // _WIN32

namespace peanut {

class Thread : noncopyable {
 public:
  typedef std::function<void()> ThreadFunc;

  explicit Thread(ThreadFunc, const string &name = string());
  // FIXME: make it movable in C++11
  ~Thread();

  void start();
  int join();

  bool started() const { return started_; }

  pid_t tid() const { return tid_; }
  const string &name() const { return name_; }

  static int numCreated() { return numCreated_.get(); }

 private:
  void setDefaultName();

  bool started_;
  bool joined_;
  pid_t tid_;
  ThreadFunc func_;
  string name_;
  CountDownLatch latch_;
  std::shared_ptr<std::thread> pthread_;

  static AtomicInt32 numCreated_;
};

}  // namespace peanut
#endif  // PEANUT_BASE_THREAD_H
