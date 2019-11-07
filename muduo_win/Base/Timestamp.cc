// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "Timestamp.h"

//#include <sys/time.h>
#include <stdio.h>
#include <time.h>

#include <chrono>

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <inttypes.h>

using namespace muduo;

// static_assert(sizeof(Timestamp) == sizeof(int64_t),
//              "Timestamp is same size as int64_t");

string Timestamp::toString() const {
  char buf[32] = {0};
  int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
  int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
  snprintf(buf, sizeof(buf) - 1, "%" PRId64 ".%06" PRId64 "", seconds,
           microseconds);
  return buf;
}

string Timestamp::toFormattedString(bool showMicroseconds) const {
  char buf[64] = {0};
  time_t seconds =
      static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
  struct tm tm_time;
  gmtime_s(&tm_time, &seconds);

  if (showMicroseconds) {
    int microseconds =
        static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
    snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
             tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
             tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, microseconds);
  } else {
    snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
             tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
             tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
  }
  return buf;
}
/*
#include <Windows.h>
int gettimeofday(struct timeval* tp, struct timezone* tzp) {
  int64_t microSeconds =
      std::chrono::system_clock::now().time_since_epoch().count() / 10;
  tp->tv_sec = (long)(microSeconds / 1000000);
  tp->tv_usec = (long)(microSeconds % 1000000);

  return 0;
}*/

Timestamp Timestamp::now() {
  int64_t microSecondsSinceEpochArg =
      std::chrono::system_clock::now().time_since_epoch().count() / 10;
  return Timestamp(microSecondsSinceEpochArg);
  /*struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t seconds = tv.tv_sec;
  return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);*/

}
