# add_executable(atomic_test atomic_test.cpp)

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

add_executable(gtest_main gtest_main.cpp colorprint_test.cpp config_test.cpp stringutil_test.cpp atomic_test.cpp)
target_link_libraries(gtest_main GTest::GTest)

# set(TESTDATA_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#if(CMAKE_BUILD_TYPE STREQUAL "Release")
#    set(TESTDATA_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release")
#else()
#    set(TESTDATA_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
#endif()
#message("testdat: " ${CMAKE_BUILD_TYPE})
#message("TESTDATA_DIR: " ${TESTDATA_DIR})
#file(COPY ./testdata DESTINATION ${TESTDATA_DIR})

############################################################
# Install
############################################################

# Binaries
install (TARGETS blockingqueue_bench blockingqueue_test 
    boundedblockingqueue_test gzipfile_test singleton_test
    threadpool_test gtest_main
    DESTINATION bin)

# Tessdata
install(DIRECTORY ${PROJECT_SOURCE_DIR}/test/testdata
    DESTINATION bin/)