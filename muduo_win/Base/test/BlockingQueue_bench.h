#pragma once
#include "../BlockingQueue.h"
#include "../CountDownLatch.h"
#include "../Thread.h"
#include "../Timestamp.h"
#include "public.h"

#include <stdio.h>
//#include <unistd.h>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <Windows.h>

namespace peanut {

template <typename T>
class BlockingQueue : muduo::noncopyable {
 public:
  BlockingQueue() : mutex_(), notEmpty_(), queue_() {}

  void put(const T& x) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push_back(x);
    notEmpty_.notify_one();  // wait morphing saves us
    // http://www.domaigne.com/blog/computing/condvars-signal-with-mutex-locked-or-not/
  }

  void put(T&& x) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push_back(std::move(x));
    notEmpty_.notify_one();
  }

  T take() {
    std::unique_lock<std::mutex> lock(mutex_);
    // always use a while-loop, due to spurious wakeup
    while (queue_.empty()) {
      notEmpty_.wait(lock);
    }
    assert(!queue_.empty());
    T front(std::move(queue_.front()));

    queue_.pop_front();

    return std::move(front);
  }

  size_t size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
  }

 private:
  mutable std::mutex mutex_;
  std::condition_variable notEmpty_;
  std::deque<T> queue_;
};
}  // namespace peanut

class Bench {
 public:
  Bench(int numThreads) : latch_(numThreads) {
    for (int i = 0; i < numThreads; ++i) {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      threads_.emplace_back(new muduo::Thread(
          std::bind(&Bench::threadFunc, this), muduo::string(name)));
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
      muduo::Timestamp now(muduo::Timestamp::now());
      queue_.put(now);
      std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
  }

  void joinAll() {
    for (size_t i = 0; i < threads_.size(); ++i) {
      queue_.put(muduo::Timestamp::invalid());
    }

    for (auto& thr : threads_) {
      thr->join();
    }
  }

 private:
  void threadFunc() {
    myprintf("tid=%lld, %s started\n", muduo::CurrentThread::tid(),
           muduo::CurrentThread::name());

    std::map<int, int> delays;
    latch_.countDown();
    bool running = true;
    while (running) {
      muduo::Timestamp t(queue_.take());
      muduo::Timestamp now(muduo::Timestamp::now());
      if (t.valid()) {
        int delay = static_cast<int>(timeDifference(now, t) * 1000000);
        // printf("tid=%d, latency = %d us\n",
        //        muduo::CurrentThread::tid(), delay);
        ++delays[delay];
      }
      running = t.valid();
    }

    myprintf("tid=%lld, %s stopped\n", muduo::CurrentThread::tid(),
           muduo::CurrentThread::name());
    for (const auto& delay : delays) {
      myprintf("tid = %lld, delay = %d, count = %d\n", muduo::CurrentThread::tid(),
             delay.first, delay.second);
    }
  }

  muduo::BlockingQueue<muduo::Timestamp> queue_;
  muduo::CountDownLatch latch_;
  std::vector<std::unique_ptr<muduo::Thread>> threads_;
};

int blockingQueue_bench(int threadNum) {
  int threads = threadNum > 1 ? threadNum : 1;

  Bench t(threads);
  t.run(10000);
  t.joinAll();

  return 0;
}
