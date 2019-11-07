#pragma once
#include "../BoundedBlockingQueue.h"
#include "../CountDownLatch.h"
#include "../Thread.h"
#include "public.h"

#include <string>
#include <vector>

#include <stdio.h>
//#include <unistd.h>
#include <Windows.h>

class TestBounded {
 public:
  TestBounded(int numThreads)
      : queue_(20), latch_(numThreads) {
    for (int i = 0; i < numThreads; ++i) {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      threads_.emplace_back(new muduo::Thread(
          std::bind(&TestBounded::threadFunc, this), muduo::string(name)));
    }
    for (auto& thr : threads_) {
      thr->start();
    }
  }

  void run(int times) {
    myprintf("waiting for count down latch\n");
    latch_.wait();
    myprintf("all threads started\n");
    for (int i = 0; i < times; ++i) {
      char buf[32];
      snprintf(buf, sizeof buf, "hello %d", i);
      queue_.put(buf);
      myprintf("tid=%lld, put data = %s, size = %zd\n",
               muduo::CurrentThread::tid(), buf, queue_.size());
    }
  }

  void joinAll() {
    for (size_t i = 0; i < threads_.size(); ++i) {
      queue_.put("stop");
    }

    for (auto& thr : threads_) {
      thr->join();
    }
  }

 private:
  void threadFunc() {
    myprintf("tid=%lld, %s started\n", muduo::CurrentThread::tid(),
             muduo::CurrentThread::name());

    latch_.countDown();
    bool running = true;
    while (running) {
      std::string d(queue_.take());
      myprintf("tid=%lld, get data = %s, size = %zd\n",
               muduo::CurrentThread::tid(), d.c_str(), queue_.size());
      running = (d != "stop");
    }

    myprintf("tid=%lld, %s stopped\n", muduo::CurrentThread::tid(),
             muduo::CurrentThread::name());
  }

  muduo::BoundedBlockingQueue<std::string> queue_;
  muduo::CountDownLatch latch_;
  std::vector<std::unique_ptr<muduo::Thread>> threads_;
};

int boundedBlockingQueue_test() {
  myprintf("pid=%ld, tid=%lld\n", GetCurrentProcessId(),
           muduo::CurrentThread::tid());
  TestBounded t(5);
  t.run(100);
  t.joinAll();

  myprintf("number of created threads %d\n", muduo::Thread::numCreated());

  return 0;
}
