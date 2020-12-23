// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_CURRENTTHREAD_H
#define PEANUT_BASE_CURRENTTHREAD_H

#include <atomic>
#include <thread>

#include "Types.h"

#if defined _WIN32
typedef unsigned long pid_t;
#endif  // _WIN32

namespace peanut {
namespace CurrentThread {
// internal
extern __thread pid_t t_cachedTid;
extern __thread char t_tidString[32];
extern __thread int t_tidStringLength;
extern __thread const char *t_threadName;
void cacheTid();

inline pid_t tid() {
  if (t_cachedTid == 0) {
    cacheTid();
  }
  return t_cachedTid;
}

inline const char *tidString()  // for logging
{
  return t_tidString;
}

inline int tidStringLength()  // for logging
{
  return t_tidStringLength;
}

inline const char *name() { return t_threadName; }

// 微秒（µs）：10-6秒
inline void sleepUsec(int64_t usec)  // for testing
{
  std::this_thread::sleep_for(std::chrono::microseconds(usec));
}

string stackTrace(bool demangle);
}  // namespace CurrentThread
}  // namespace peanut

#endif  // PEANUT_BASE_CURRENTTHREAD_H
