#pragma once
#include "../BlockingQueue.h"
#include "../CountDownLatch.h"
#include "../Mutex.h"
#include "../Thread.h"
#include "public.h"

#include <stdio.h>
//#include <unistd.h>
#include <Windows.h>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>
using namespace std;



template <typename T>
class BlockingQueueWithLog : muduo::noncopyable {
 public:
  BlockingQueueWithLog() : mutex_(), notEmpty_(mutex_), queue_() {}

  void put(const T& x) {
    muduo::MutexLockGuard lock(mutex_);
    queue_.push_back(x);
    notEmpty_.notify();  // wait morphing saves us
    // http://www.domaigne.com/blog/computing/condvars-signal-with-mutex-locked-or-not/
    cout << "tid=" << muduo::CurrentThread::tid() << ",putdata=" << x
         << ",size=" << queue_.size() << endl;
  }

  void put(T&& x) {
    muduo::MutexLockGuard lock(mutex_);
    queue_.push_back(std::move(x));
    notEmpty_.notify();
    cout << "tid=" << muduo::CurrentThread::tid() << ",putdata=" << x
         << ",size=" << queue_.size() << endl;
  }

  T take() {
    muduo::MutexLockGuard lock(mutex_);
    // always use a while-loop, due to spurious wakeup
    while (queue_.empty()) {
      notEmpty_.wait();
    }
    assert(!queue_.empty());
    T front(std::move(queue_.front()));

    queue_.pop_front();

    cout << "tid=" << muduo::CurrentThread::tid() << ",getdata=" << front
         << ",size=" << queue_.size() << endl;

    return std::move(front);
  }

  size_t size() const {
    MutexLockGuard lock(mutex_);
    return queue_.size();
  }

 private:
  mutable muduo::MutexLock mutex_;
  muduo::Condition notEmpty_;
  std::deque<T> queue_;
};

class Test {
 public:
  Test(int numThreads) : latch_(numThreads) {
    for (int i = 0; i < numThreads; ++i) {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      threads_.emplace_back(new muduo::Thread(
          std::bind(&Test::threadFunc, this), muduo::string(name)));
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
      // myprintf("tid=%lld, put data = %s, size = %zd\n",
      //         muduo::CurrentThread::tid(),
      //       buf, queue_.size());
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
      std::string d(queue_.take());  //
      // myprintf("tid=%lld, get data = %s, size = %zd\n",
      // muduo::CurrentThread::tid(),
      //       d.c_str(), queue_.size());
      running = (d != "stop");
    }

    myprintf("tid=%lld, %s stopped\n", muduo::CurrentThread::tid(),
             muduo::CurrentThread::name());
  }

  // muduo::BlockingQueue<std::string> queue_;
  BlockingQueueWithLog<std::string> queue_;

  muduo::CountDownLatch latch_;
  std::vector<std::unique_ptr<muduo::Thread>> threads_;
};

void testMove() {
  muduo::BlockingQueue<std::unique_ptr<int>> queue;
  queue.put(std::unique_ptr<int>(new int(42)));
  std::unique_ptr<int> x = queue.take();
  myprintf("took %d\n", *x);
  *x = 123;
  queue.put(std::move(x));
  std::unique_ptr<int> y = queue.take();
  myprintf("took %d\n", *y);
}

int blockingQueue_test() {
  myprintf("pid=%ld, tid=%lld\n", GetCurrentProcessId(),
           muduo::CurrentThread::tid());
  Test t(4);
  t.run(100);
  t.joinAll();

  testMove();

  myprintf("number of created threads %d\n", muduo::Thread::numCreated());

  return 0;
}
