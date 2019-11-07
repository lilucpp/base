#pragma once
#include <functional>
#include "../CurrentThread.h"
#include "../Exception.h"
#include <stdio.h>
#include <vector>


class Bar {
public:
  void test(std::vector<std::string> names = {}) {
    printf("Stack:\n%s\n", muduo::CurrentThread::stackTrace(true).c_str());
    [] {
      printf("Stack inside lambda:\n%s\n",
             muduo::CurrentThread::stackTrace(true).c_str());
    }();
    std::function<void()> func([] {
      printf("Stack inside std::function:\n%s\n",
             muduo::CurrentThread::stackTrace(true).c_str());
    });
    func();

    func = std::bind(&Bar::callback, this);
    func();

    throw muduo::Exception("oops");
  }

private:
  void callback() {
    printf("Stack inside std::bind:\n%s\n",
           muduo::CurrentThread::stackTrace(true).c_str());
  }
};

int foo() {
  Bar b;
  b.test();

  return 0;
}
