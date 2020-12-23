// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#include "Condition.h"

#include <errno.h>

#include <chrono>

namespace peanut {

// returns true if time out, false otherwise.
bool Condition::waitForSeconds(double seconds) {
  const int64_t kNanoSecondsPerSecond = 1000000000;
  int64_t nanoseconds = static_cast<int64_t>(seconds * kNanoSecondsPerSecond);
  auto now = std::chrono::high_resolution_clock::now();
  auto abstime = now + std::chrono::nanoseconds(nanoseconds);

  MutexLock::UnassignGuard ug(mutex_);
  return std::cv_status::timeout == pcond_.wait_until(mutex_, abstime);
}

}  // namespace peanut
