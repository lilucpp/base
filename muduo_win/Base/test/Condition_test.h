#pragma once
#include <chrono>
#include <iostream>
#include <thread>
#include "../Exception.h"
#include "../Condition.h"
#include "../Mutex.h"
#include "../Thread.h"

class Condition_test {
 public:
  Condition_test(double timeout) : lock_(), cond_(lock_), timeout_(timeout) {}

  void notify() {
    std::cout << "notify start..." << std::endl;
    muduo::CurrentThread::sleepUsec(2 * 1000 * 1000);
    {
      std::cout << "notify: before notifyall..." << std::endl;
      muduo::MutexLockGuard lck(lock_);
      cond_.notifyAll();
      std::cout << "notify: after notifyall..." << std::endl;
    }

    std::cout << "notify end..." << std::endl;
  }

  void waitthread() {
    std::cout << "wait start..." << std::endl;
    {
      muduo::MutexLockGuard lck(lock_);
      if (!cond_.waitForSeconds(timeout_))
        std::cout << "***waitthread: wait success..." << std::endl;
      else {
        std::cout << "***waitthread: wait timeout..." << std::endl;
      }
       
    }
    std::cout << "wait end..." << std::endl;
  }

 private:
  muduo::MutexLock lock_;
  muduo::Condition cond_;
  double timeout_;
};

int condition_test(double timeout) {
  std::cout << "condition_test: wait time = " << timeout << "" << std::endl;
  Condition_test test(timeout);
  muduo::Thread wait(std::bind(&Condition_test::waitthread, &test));
  wait.start();

  muduo::Thread notify(std::bind(&Condition_test::notify, &test));
  notify.start();

  notify.join();
  wait.join();
  std::cout << std::endl;
  return 0;
}