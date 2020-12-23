// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_COUNTDOWNLATCH_H
#define PEANUT_BASE_COUNTDOWNLATCH_H

#include "Condition.h"
#include "Mutex.h"

namespace peanut {

class CountDownLatch : noncopyable {
 public:
  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  int getCount();

 private:
  MutexLock mutex_;
  Condition condition_;
  int count_;
};

}  // namespace peanut
#endif  // PEANUT_BASE_COUNTDOWNLATCH_H
