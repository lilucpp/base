// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "Thread.h"
#include "CurrentThread.h"
#include "Exception.h"
#include "Timestamp.h"
//#include "Logging.h"

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <windows.h>

#include <sstream>
#include <type_traits>

namespace muduo {
namespace detail {

// https://github.com/facebook/folly/blob/master/folly/system/ThreadName.cpp
static constexpr size_t kMaxThreadNameLength = 16;
bool setThreadName(std::thread::id tid, const string &name) {
  auto trimmedName = name.substr(0, kMaxThreadNameLength - 1);
  static_assert(sizeof(unsigned int) == sizeof(std::thread::id),
                "This assumes std::thread::id is a thin wrapper around "
                "the thread id as an unsigned int, but that doesn't appear to be true.");

// http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
#pragma pack(push, 8)
  struct THREADNAME_INFO {
    DWORD dwType;      // Must be 0x1000
    LPCSTR szName;     // Pointer to name (in user address space)
    DWORD dwThreadID;  // Thread ID (-1 for caller thread)
    DWORD dwFlags;     // Reserved for future use; must be zero
  };
  union TNIUnion {
    THREADNAME_INFO tni;
    ULONG_PTR upArray[4];
  };
#pragma pack(pop)

  static constexpr DWORD kMSVCException = 0x406D1388;

  // std::thread::id is a thin wrapper around an integral thread id,
  // so just extract the ID.
  unsigned int id;
  std::memcpy(&id, &tid, sizeof(id));

  TNIUnion tniUnion = {0x1000, trimmedName.data(), id, 0};
  // This has to be in a separate stack frame from trimmedName, which requires
  // C++ object destruction semantics.
  return [&]() {
    __try {
      RaiseException(kMSVCException, 0, 4, tniUnion.upArray);
    } __except (GetExceptionCode() == kMSVCException ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_EXECUTE_HANDLER) {
      // Swallow the exception when a debugger isn't attached.
    }
    return true;
  }();
}

#if defined(_WIN32)
pid_t gettid() { return GetCurrentThreadId(); }
#endif  // _WIN32

class ThreadNameInitializer {
 public:
  ThreadNameInitializer() {
    muduo::CurrentThread::t_threadName = "main";
    CurrentThread::tid();
  }
};

ThreadNameInitializer init;

struct ThreadData {
  typedef muduo::Thread::ThreadFunc ThreadFunc;
  ThreadFunc func_;
  string name_;
  pid_t *tid_;
  CountDownLatch *latch_;

  ThreadData(ThreadFunc func, const string &name, pid_t *tid, CountDownLatch *latch)
      : func_(std::move(func)), name_(name), tid_(tid), latch_(latch) {}

  void runInThread() {
    *tid_ = muduo::CurrentThread::tid();
    tid_ = NULL;
    latch_->countDown();
    latch_ = NULL;

    muduo::CurrentThread::t_threadName = name_.empty() ? "muduoThread" : name_.c_str();
    setThreadName(std::this_thread::get_id(), muduo::CurrentThread::t_threadName);
    try {
      func_();
      muduo::CurrentThread::t_threadName = "finished";
    } catch (const Exception &ex) {
      muduo::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
      abort();
    } catch (const std::exception &ex) {
      muduo::CurrentThread::t_threadName = "crashed";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      abort();
    } catch (...) {
      muduo::CurrentThread::t_threadName = "crashed";
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

}  // namespace muduo
