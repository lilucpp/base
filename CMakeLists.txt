cmake_minimum_required(VERSION 3.10)

set(BUILD_SHARED_LIBS ON)
set(CMAKE_CXX_STANDARD 11)              # Compile as C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require C++11 support

project(Peanut
        VERSION 0.0.1
        DESCRIPTION "The BusTub Base Library (lilu) @ https://github.com/lilucpp/base"
        LANGUAGES CXX
        )

if(MSVC)
	add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MT> #--|
	)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

find_package(Boost)
find_package(GTest REQUIRED)
find_package(ZLIB REQUIRED)

if(ZLIB_FOUND)
    message("zlib dir: " ${ZLIB_INCLUDE_DIRS})
    message("zlib libraries: " ${ZLIB_LIBRARIES})
else()
    message(GTEST_LIBRARIES "Cannot found zlib")
endif()

if(GTEST_FOUND)
    message("gtest dir: " ${GTEST_INCLUDE_DIRS})
    message("gtest libraries: " ${GTEST_LIBRARIES})
else()
    message(GTEST_LIBRARIES "Cannot found gtest")
endif()

# check if boost was found
if(Boost_FOUND)
    message("boost dir: " ${GTEST_LIBRARIES})
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

# People keep running CMake in the wrong folder, completely nuking their project or creating weird bugs.
# This checks if you're running CMake from a folder that already has CMakeLists.txt.
# Importantly, this catches the common case of running it from the root directory.
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)
if (EXISTS "${PATH_TO_CMAKELISTS_TXT}")
    message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif ()

# Includes.
set(PEANUT_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)
