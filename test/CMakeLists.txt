add_executable(blockingqueue_test blockingqueue_test.cpp)
target_link_libraries(blockingqueue_test PeanutBase)

add_executable(threadpool_test threadpool_test.cpp)
target_link_libraries(threadpool_test PeanutBase)