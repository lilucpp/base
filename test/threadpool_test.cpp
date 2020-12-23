#include "../src/ThreadPool.h"
#include "../src/CountDownLatch.h"
#include "../src/CurrentThread.h"

#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>

//#include <unistd.h>  // usleep

void print() { printf("tid=%d\n", peanut::CurrentThread::tid()); }
void usleep(int usec) { std::this_thread::sleep_for(std::chrono::microseconds(usec)); }

void printString(const std::string &str) {
  std::cout << str << std::endl;
  usleep(100 * 1000);
}

void test(int maxSize) {
  std::cout << "Test ThreadPool with max queue size = " << maxSize << std::endl;
  peanut::ThreadPool pool("MainThreadPool");
  pool.setMaxQueueSize(maxSize);
  pool.start(5);

  std::cout << "Adding" << std::endl;
  pool.run(print);
  pool.run(print);
  for (int i = 0; i < 100; ++i) {
    char buf[32];
    snprintf(buf, sizeof buf, "task %d", i);
    pool.run(std::bind(printString, std::string(buf)));
  }
  std::cout << "Done" << std::endl;
  std::cout << "---queueSize=" << pool.queueSize() << std::endl;
  peanut::CountDownLatch latch(1);
  pool.run(std::bind(&peanut::CountDownLatch::countDown, &latch));
  latch.wait();
  std::cout << "---queueSize=" << pool.queueSize() << std::endl;
  pool.stop();
}

/*
 * Wish we could do this in the future.
void testMove()
{
  peanut::ThreadPool pool;
  pool.start(2);

  std::unique_ptr<int> x(new int(42));
  pool.run([y = std::move(x)]{ printf("%d: %d\n", peanut::CurrentThread::tid(),
*y); }); pool.stop();
}
*/

void longTask(int num) {
  std::cout << "longTask " << num << std::endl;
  peanut::CurrentThread::sleepUsec(3000000);
}

void test2() {
  std::cout << "Test ThreadPool by stoping early." << std::endl;
  peanut::ThreadPool pool("ThreadPool");
  pool.setMaxQueueSize(5);
  pool.start(3);

  peanut::Thread thread1(
      [&pool]() {
        for (int i = 0; i < 20; ++i) {
          pool.run(std::bind(longTask, i));
        }
      },
      "thread1");
  thread1.start();

  peanut::CurrentThread::sleepUsec(7000000);
  std::cout << "stop pool" << std::endl;
  pool.stop();  // early stop

  thread1.join();
  // run() after stop()
  pool.run(print);
  std::cout << "test2 Done" << std::endl;
}

int main() {
  test(0);
  test(1);
  test(5);
  test(10);
  test(50);
  test2();
}
