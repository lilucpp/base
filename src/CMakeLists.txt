set(base_SRCS
Condition.cc
CountDownLatch.cc
CurrentThread.cc
Date.cc
Exception.cc
Timestamp.cc
Thread.cc
ThreadPool.cc
)
    
add_library(PeanutBase STATIC ${base_SRCS})
# target_link_libraries(bustub_shared thirdparty_murmur3)