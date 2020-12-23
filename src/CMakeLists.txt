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

############################################################
# Install
############################################################

# Library
install (TARGETS PeanutBase
    LIBRARY DESTINATION lib)

# Header files
install(DIRECTORY  ${PROJECT_SOURCE_DIR}/src/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h")