// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#include <stdlib.h>
#include "CurrentThread.h"

#include "boost/stacktrace.hpp"

namespace peanut {
namespace CurrentThread {
__thread pid_t t_cachedTid = 0;
__thread char t_tidString[32];
__thread int t_tidStringLength = 6;
__thread const char *t_threadName = "unknown";

static_assert(std::is_same<unsigned long, pid_t>::value, "pid_t should be unsigned long");
string stackTrace(bool demangle) { return boost::stacktrace::to_string(boost::stacktrace::stacktrace()); }

}  // namespace CurrentThread
}  // namespace peanut
