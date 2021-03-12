set(base_SRCS
Condition.cpp
CountDownLatch.cpp
Date.cpp
Exception.cpp
StringUtil.cpp
Timestamp.cpp
ThreadPool.cpp
Application.cpp
)

if(UNIX)
    set(base_SRCS
    ${base_SRCS}
    CurrentThread_Linux.cpp
    Thread_Linux.cpp
    )

else()
    set(base_SRCS
    ${base_SRCS}
    CurrentThread_Win32.cpp
    Thread_Win32.cpp
    )

endif()

add_library(PeanutBase STATIC ${base_SRCS})
target_link_libraries(PeanutBase ${Boost_LIBRARIES} fmt)
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
