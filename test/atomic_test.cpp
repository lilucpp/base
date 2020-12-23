#include "../src/Atomic.h"
#include "gtest/gtest.h"

TEST(Atomic, TestAtomicInt64) {
  muduo::AtomicInt64 a0;
  ASSERT_TRUE(a0.get() == 0);
  ASSERT_TRUE(a0.getAndAdd(1) == 0);
  ASSERT_TRUE(a0.get() == 1);
  ASSERT_TRUE(a0.addAndGet(2) == 3);
  ASSERT_TRUE(a0.get() == 3);
  ASSERT_TRUE(a0.incrementAndGet() == 4);
  ASSERT_TRUE(a0.get() == 4);
  a0.increment();
  ASSERT_TRUE(a0.get() == 5);
  ASSERT_TRUE(a0.addAndGet(-3) == 2);
  ASSERT_TRUE(a0.getAndSet(100) == 2);
  ASSERT_TRUE(a0.get() == 100);
}

TEST(Atomic, TestAtomicInt32) {
  muduo::AtomicInt32 a1;
  ASSERT_TRUE(a1.get() == 0);
  ASSERT_TRUE(a1.getAndAdd(1) == 0);
  ASSERT_TRUE(a1.get() == 1);
  ASSERT_TRUE(a1.addAndGet(2) == 3);
  ASSERT_TRUE(a1.get() == 3);
  ASSERT_TRUE(a1.incrementAndGet() == 4);
  ASSERT_TRUE(a1.get() == 4);
  a1.increment();
  ASSERT_TRUE(a1.get() == 5);
  ASSERT_TRUE(a1.addAndGet(-3) == 2);
  ASSERT_TRUE(a1.getAndSet(100) == 2);
  ASSERT_TRUE(a1.get() == 100);
}
