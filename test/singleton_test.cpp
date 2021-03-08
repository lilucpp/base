#include "../src/Singleton.h"
#include "../src/CurrentThread.h"
#include "../src/Thread.h"

#include <stdio.h>

class Test : peanut::noncopyable {
 public:
  Test() { printf("tid=%d, constructing %p\n", peanut::CurrentThread::tid(), static_cast<void *>(this)); }

  ~Test() {
    printf("tid=%d, destructing %p %s\n", peanut::CurrentThread::tid(), static_cast<void *>(this), name_.c_str());
  }

  const peanut::string &name() const { return name_; }
  void setName(const peanut::string &n) { name_ = n; }

 private:
  peanut::string name_;
};

class TestNoDestroy : peanut::noncopyable {
 public:
  // Tag member for Singleton<T>
  void no_destroy();

  TestNoDestroy() {
    printf("tid=%d, constructing TestNoDestroy %p\n", peanut::CurrentThread::tid(), static_cast<void *>(this));
  }

  ~TestNoDestroy() {
    printf("tid=%d, destructing TestNoDestroy %p\n", peanut::CurrentThread::tid(), static_cast<void *>(this));
  }
};

void threadFunc() {
  printf("tid=%d, %p name=%s\n", peanut::CurrentThread::tid(),
         static_cast<void *>(&peanut::Singleton<Test>::instance()), peanut::Singleton<Test>::instance().name().c_str());
  peanut::Singleton<Test>::instance().setName("only one, changed");
}

int main() {
  peanut::Singleton<Test>::instance().setName("only one");
  peanut::Thread t1(threadFunc);
  t1.start();
  t1.join();
  printf("tid=%d, %p name=%s\n", peanut::CurrentThread::tid(),
         static_cast<void *>(&peanut::Singleton<Test>::instance()), peanut::Singleton<Test>::instance().name().c_str());
  peanut::Singleton<TestNoDestroy>::instance();
  printf("with valgrind, you should see %zd-byte memory leak.\n", sizeof(TestNoDestroy));
}
