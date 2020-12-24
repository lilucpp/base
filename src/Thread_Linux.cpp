// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#include "CurrentThread.h"
#include "Exception.h"
#include "Thread.h"
#include "Timestamp.h"

#include <errno.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <type_traits>

namespace peanut {
namespace detail {

pid_t gettid() { return static_cast<pid_t>(::syscall(SYS_gettid)); }

void afterFork() {
  muduo::CurrentThread::t_cachedTid = 0;
  muduo::CurrentThread::t_threadName = "main";
  CurrentThread::tid();
  // no need to call pthread_atfork(NULL, NULL, &afterFork);
}

class ThreadNameInitializer {
 public:
  ThreadNameInitializer() {
    peanut::CurrentThread::t_threadName = "main";
    CurrentThread::tid();
    pthread_atfork(NULL, NULL, &afterFork);
  }
};

ThreadNameInitializer init;

struct ThreadData {
  typedef peanut::Thread::ThreadFunc ThreadFunc;
  ThreadFunc func_;
  string name_;
  pid_t *tid_;
  CountDownLatch *latch_;

  ThreadData(ThreadFunc func, const string &name, pid_t *tid, CountDownLatch *latch)
      : func_(std::move(func)), name_(name), tid_(tid), latch_(latch) {}

  void runInThread() {
    *tid_ = peanut::CurrentThread::tid();
    tid_ = NULL;
    latch_->countDown();
    latch_ = NULL;

    peanut::CurrentThread::t_threadName = name_.empty() ? "peanutThread" : name_.c_str();
    ::prctl(PR_SET_NAME, peanut::CurrentThread::t_threadName);
    try {
      func_();
      peanut::CurrentThread::t_threadName = "finished";
    } catch (const Exception &ex) {
      peanut::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
      abort();
    } catch (const std::exception &ex) {
      peanut::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      abort();
    } catch (...) {
      peanut::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
      throw;  // rethrow
    }
  }
};

void *startThread(void *obj) {
  ThreadData *data = static_cast<ThreadData *>(obj);
  data->runInThread();
  delete data;
  return NULL;
}

}  // namespace detail

void CurrentThread::cacheTid() {
  if (t_cachedTid == 0) {
    t_cachedTid = detail::gettid();

    t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
  }
}

AtomicInt32 Thread::numCreated_;

Thread::Thread(ThreadFunc func, const string &n)
    : started_(false), joined_(false), tid_(), func_(std::move(func)), name_(n), latch_(1), pthread_() {
  setDefaultName();
}

Thread::~Thread() {
  if (started_ && !joined_) {
    pthread_->detach();
  }
}

void Thread::setDefaultName() {
  int num = numCreated_.incrementAndGet();
  if (name_.empty()) {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", num);
    name_ = buf;
  }
}

void Thread::start() {
  assert(!started_);
  started_ = true;
  // FIXME: move(func_)
  detail::ThreadData *data = new detail::ThreadData(func_, name_, &tid_, &latch_);
  pthread_ = std::make_shared<std::thread>(std::thread(&detail::startThread, data));
  if (!pthread_) {
    started_ = false;
    delete data;  // or no delete?
    //?LOG_SYSFATAL << "Failed in pthread_create";
  } else {
    latch_.wait();
    assert(tid_ > 0);
  }
}

int Thread::join() {
  assert(started_);
  assert(!joined_);
  joined_ = true;
  pthread_->join();
  return 0;
}

}  // namespace peanut
