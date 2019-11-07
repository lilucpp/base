#pragma once
//#define BOOST_TEST_MODULE Atomiac_test
#include <boost/test/included/unit_test.hpp>
#include "../Atomic.h"

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(test_AtomiacInt64) {
  muduo::AtomicInt64 a0;
  BOOST_CHECK(a0.get() == 0);
  BOOST_CHECK(a0.getAndAdd(1) == 0);
  BOOST_CHECK(a0.get() == 1);
  BOOST_CHECK(a0.addAndGet(2) == 3);
  BOOST_CHECK(a0.get() == 3);
  BOOST_CHECK(a0.incrementAndGet() == 4);
  BOOST_CHECK(a0.get() == 4);
  a0.increment();
  BOOST_CHECK(a0.get() == 5);
  BOOST_CHECK(a0.addAndGet(-3) == 2);
  BOOST_CHECK(a0.getAndSet(100) == 2);
  BOOST_CHECK(a0.get() == 100);
} 

BOOST_AUTO_TEST_CASE(test_AtomiacInt32) {
  muduo::AtomicInt32 a1;
  BOOST_CHECK(a1.get() == 0);
  BOOST_CHECK(a1.getAndAdd(1) == 0);
  BOOST_CHECK(a1.get() == 1);
  BOOST_CHECK(a1.addAndGet(2) == 3);
  BOOST_CHECK(a1.get() == 3);
  BOOST_CHECK(a1.incrementAndGet() == 4);
  BOOST_CHECK(a1.get() == 4);
  a1.increment();
  BOOST_CHECK(a1.get() == 5);
  BOOST_CHECK(a1.addAndGet(-3) == 2);
  BOOST_CHECK(a1.getAndSet(100) == 2);
  BOOST_CHECK(a1.get() == 100);
}

BOOST_AUTO_TEST_SUITE_END()