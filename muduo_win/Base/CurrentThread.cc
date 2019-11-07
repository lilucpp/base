// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "CurrentThread.h"

//#include <cxxabi.h>
//#include <execinfo.h>
#include <stdlib.h>

#include "boost/stacktrace.hpp"

namespace muduo {
namespace CurrentThread {
__thread pid_t t_cachedTid = 0;
__thread char t_tidString[32];
__thread int t_tidStringLength = 6;
__thread const char* t_threadName = "unknown";
std::atomic_uint64_t g_mainTid = 0;
static_assert(std::is_same<uint64_t, pid_t>::value, "pid_t should be uint64_t");

string stackTrace(bool demangle) {
  return boost::stacktrace::to_string(boost::stacktrace::stacktrace());
}

}  // namespace CurrentThread
}  // namespace muduo
