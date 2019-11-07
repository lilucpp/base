#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include "test/Atomiac_test.h"
#include "test/Exception_test.h"
#include "test/Thread_test.h"
#include "test/Timestamp_test.h"
#include "test/Condition_test.h"
#include "test/BlockingQueue_test.h"
#include "test/BoundedBlockingQueue_test.h"
#include "test/BlockingQueue_bench.h"

bool muduoException(const muduo::Exception &ex) {
  BOOST_TEST_MESSAGE("muduoException test:" << ex.what());
  BOOST_TEST_MESSAGE("exception stackTrace:\n" << ex.stackTrace());
  BOOST_CHECK_EQUAL(ex.what(), std::string("oops"));
  return true;
}

bool muduoExceptionTimeout(const muduo::Exception &ex) {
  BOOST_CHECK_EQUAL(ex.what(), std::string("timeout"));
  return true;
}

BOOST_AUTO_TEST_CASE(case_foo) {
  BOOST_TEST_MESSAGE("init");
  BOOST_CHECK_EXCEPTION(foo(), muduo::Exception, muduoException);
}

BOOST_AUTO_TEST_CASE(case_thread) {
  BOOST_TEST_MESSAGE("thread test start...");
  BOOST_CHECK_EQUAL(thread_test(), 0);
}

BOOST_AUTO_TEST_CASE(case_timestamp) {
  BOOST_TEST_MESSAGE("timestamp test start...");
  BOOST_CHECK_EQUAL(timestamp_test(), 0);
}

BOOST_AUTO_TEST_CASE(case_condition) {
  BOOST_TEST_MESSAGE("condition test start...");

  BOOST_CHECK_EQUAL(condition_test(1),0);
  BOOST_CHECK_EQUAL(condition_test(2),0);
  BOOST_CHECK_EQUAL(condition_test(3),0);
  BOOST_CHECK_EQUAL(condition_test(4),0);
}

BOOST_AUTO_TEST_CASE(case_blockingqueue) {
  BOOST_TEST_MESSAGE("blockingqueue test start...");
  BOOST_CHECK_EQUAL(blockingQueue_test(), 0); 
}

BOOST_AUTO_TEST_CASE(case_boundedblockingqueue) {
  BOOST_TEST_MESSAGE("bounded blocking test start...");
  BOOST_CHECK_EQUAL(boundedBlockingQueue_test(), 0);
}

BOOST_AUTO_TEST_CASE(case_blockingqueuebench) {
  BOOST_TEST_MESSAGE("blocking queue bench start");
  //BOOST_CHECK_EQUAL(blockingQueue_bench(1), 0);
  //BOOST_CHECK_EQUAL(blockingQueue_bench(2), 0);
  BOOST_CHECK_EQUAL(blockingQueue_bench(3), 0);
  //BOOST_CHECK_EQUAL(blockingQueue_bench(4), 0);
  //BOOST_CHECK_EQUAL(blockingQueue_bench(5), 0);
}