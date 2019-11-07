#pragma once
#include "../Mutex.h"

muduo::MutexLock mutex4print;

template <typename... T>
void myprintf(T&&... params) {
  muduo::MutexLockGuard lock(mutex4print);
  printf(std::forward<T>(params)...);
}