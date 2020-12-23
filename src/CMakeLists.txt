set(base_SRCS
Condition.cpp
CountDownLatch.cpp
CurrentThread.cpp
Date.cpp
Exception.cpp
Timestamp.cpp
Thread.cpp
ThreadPool.cpp
)
    
add_library(PeanutBase STATIC ${base_SRCS})
if(UNIX)
	target_link_libraries(PeanutBase pthread)
endif()
############################################################
# Install
############################################################

# Library
install (TARGETS PeanutBase
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)

# Header files
install(DIRECTORY  ${PROJECT_SOURCE_DIR}/src/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h")
