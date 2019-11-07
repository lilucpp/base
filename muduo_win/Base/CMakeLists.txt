set(base_SRCS
  Condition.cc
  CountDownLatch.cc
  CurrentThread.cc
  Date.cc
  Exception.cc
  FileUtil.cc
  Timestamp.cc
  Thread.cc
  )

# Set the project name
project (muduo_base)

# Add a library with the above sources
add_library(${PROJECT_NAME} ${base_SRCS})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
