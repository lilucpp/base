// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

#include <atomic>
#include <thread>

#include "Types.h"

#if defined _WIN32
typedef uint64_t pid_t;
#endif  // _WIN32

namespace muduo {
namespace CurrentThread {
// internal
extern __thread pid_t t_cachedTid;
extern __thread char t_tidString[32];
extern __thread int t_tidStringLength;
extern __thread const char* t_threadName;
extern std::atomic_uint64_t g_mainTid;
void cacheTid();

inline pid_t tid() {
  if (t_cachedTid == 0) {
    cacheTid();
  }
  return t_cachedTid;
}

inline const char* tidString()  // for logging
{
  return t_tidString;
}

inline int tidStringLength()  // for logging
{
  return t_tidStringLength;
}

inline const char* name() { return t_threadName; }

bool isMainThread();

void sleepUsec(int64_t usec);  // for testing

string stackTrace(bool demangle);
}  // namespace CurrentThread
}  // namespace muduo

#endif  // MUDUO_BASE_CURRENTTHREAD_H
