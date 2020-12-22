add_executable(atomic_test atomic_test.cpp)

add_executable(blockingqueue_bench blockingqueue_bench.cpp)
target_link_libraries(blockingqueue_bench PeanutBase)

add_executable(blockingqueue_test blockingqueue_test.cpp)
target_link_libraries(blockingqueue_test PeanutBase)

add_executable(boundedblockingqueue_test boundedblockingqueue_test.cpp)
target_link_libraries(boundedblockingqueue_test PeanutBase)

add_executable(gzipfile_test gzipfile_test.cpp)
target_link_libraries(gzipfile_test ${ZLIB_LIBRARIES})

add_executable(singleton_test singleton_test.cpp)
target_link_libraries(singleton_test PeanutBase)

add_executable(threadpool_test threadpool_test.cpp)
target_link_libraries(threadpool_test PeanutBase)

add_executable(gtest_main gtest_main.cpp colorprint_test.cpp config_test.cpp stringutil_test.cpp)
target_link_libraries(gtest_main GTest::GTest)