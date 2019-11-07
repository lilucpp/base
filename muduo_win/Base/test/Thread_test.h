#pragma once
//#define BOOST_TEST_MODULE Thread_test
#include <boost/test/included/unit_test.hpp>
#include "../CurrentThread.h"
#include "../Thread.h"

#include <stdio.h>
#include <string>
#include <thread>

#include <Windows.h>

void mysleep(int seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void threadFunc() { printf("tid=%I64d\n", muduo::CurrentThread::tid()); }

void threadFunc2(int x) {
  printf("tid=%I64d, x=%d\n", muduo::CurrentThread::tid(), x);
}

void threadFunc3() {
  printf("tid=%I64d\n", muduo::CurrentThread::tid());
  mysleep(1);
}

class Foo {
 public:
  explicit Foo(double x) : x_(x) {}

  void memberFunc() {
    printf("tid=%I64d, Foo::x_=%f\n", muduo::CurrentThread::tid(), x_);
  }

  void memberFunc2(const std::string &text) {
    printf("tid=%I64d, Foo::x_=%f, text=%s\n", muduo::CurrentThread::tid(), x_,
           text.c_str());
  }

 private:
  double x_;
};

int thread_test() {
  printf("pid=%ld, tid=%I64d\n", GetCurrentProcessId(),
         muduo::CurrentThread::tid());

  muduo::Thread t1(threadFunc);
  t1.start();
  printf("t1.tid=%I64d\n", t1.tid());
  t1.join();

  muduo::Thread t2(std::bind(threadFunc2, 42),
                   "thread for free function with argument");
  t2.start();
  printf("t2.tid=%I64d\n", t2.tid());
  t2.join();

  Foo foo(87.53);

  muduo::Thread t3(std::bind(&Foo::memberFunc, &foo),
                   "thread for member function without argument");
  t3.start();
  t3.join();

  muduo::Thread t4(
      std::bind(&Foo::memberFunc2, std::ref(foo), std::string("Shuo Chen")));
  t4.start();
  t4.join();

  {
    muduo::Thread t5(threadFunc3);
    t5.start();
    // t5 may destruct eariler than thread creation.
  }
  mysleep(2);
  {
    muduo::Thread t6(threadFunc3);
    t6.start();
    mysleep(2);
    // t6 destruct later than thread creation.
  }
  Sleep(2000);
  printf("number of created threads %d\n", muduo::Thread::numCreated());

  return 0;
}
