# CMakeList.txt : CMake project for muduo_win, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CXX_FLAGS
 -g
 # -DVALGRIND
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
 -Werror
 -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 -std=c++11
 -rdynamic
 )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "D:/workspace/vcpkg/installed/x86-windows/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "D:/workspace/vcpkg/installed/x86-windows/lib")
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR})

include_directories("./Base")

# Add source to this project's executable.
add_executable (test_base "test.cpp" )
target_link_libraries( test_base
    PRIVATE 
        muduo_base
)

add_subdirectory ("Base")

# TODO: Add tests and install targets if needed.
