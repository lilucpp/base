#include "../src/BlockingQueue.h"
#include "../src/CountDownLatch.h"
#include "../src/Thread.h"
#include "../src/Timestamp.h"

#include <stdio.h>
#if defined _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <map>
#include <string>
#include <vector>

class Bench {
 public:
  Bench(int numThreads) : latch_(numThreads) {
    threads_.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i) {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      threads_.emplace_back(new peanut::Thread(std::bind(&Bench::threadFunc, this), peanut::string(name)));
    }
    for (auto &thr : threads_) {
      thr->start();
    }
  }

  void run(int times) {
    printf("waiting for count down latch\n");
    latch_.wait();
    printf("all threads started\n");
    for (int i = 0; i < times; ++i) {
      peanut::Timestamp now(peanut::Timestamp::now());
      queue_.put(now);
#if defined _WIN32
      Sleep(1);
#else
      // std::this_thread::sleep_for(std::chrono::microseconds(10));
      usleep(1000);
#endif
    }
  }

  void joinAll() {
    for (size_t i = 0; i < threads_.size(); ++i) {
      queue_.put(peanut::Timestamp::invalid());
    }

    for (auto &thr : threads_) {
      thr->join();
    }
  }

 private:
  void threadFunc() {
    printf("tid=%d, %s started\n", peanut::CurrentThread::tid(), peanut::CurrentThread::name());

    std::map<int, int> delays;
    latch_.countDown();
    bool running = true;
    while (running) {
      peanut::Timestamp t(queue_.take());
      peanut::Timestamp now(peanut::Timestamp::now());
      if (t.valid()) {
        int delay = static_cast<int>(timeDifference(now, t) * 1000000);
        // printf("tid=%d, latency = %d us\n",
        //        peanut::CurrentThread::tid(), delay);
        ++delays[delay];
      }
      running = t.valid();
    }

    printf("tid=%d, %s stopped\n", peanut::CurrentThread::tid(), peanut::CurrentThread::name());
    for (const auto &delay : delays) {
      printf("tid = %d, delay = %d, count = %d\n", peanut::CurrentThread::tid(), delay.first, delay.second);
    }
  }

  peanut::BlockingQueue<peanut::Timestamp> queue_;
  peanut::CountDownLatch latch_;
  std::vector<std::unique_ptr<peanut::Thread>> threads_;
};

int main(int argc, char *argv[]) {
  int threads = argc > 1 ? atoi(argv[1]) : 1;

  Bench t(threads);
  t.run(2000);
  t.joinAll();

  return 0;
}
