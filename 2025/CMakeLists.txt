cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_C_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project name and version
project(advent_of_code_2025 VERSION 0.1.0 LANGUAGES C CXX)

#
# Compile flags for any build type
#
set(COMPILE_FLAGS
    -Wall
    -Wextra
    -pthread
    -Wshadow
    -Wcast-align
    -Wwrite-strings
    -Wcast-qual
    -Wconversion
    -Wunreachable-code
    -fstack-usage
    -mavx
    -mavx2
    -march=native
    -mtune=native
)

set(RELEASE_FLAGS
    -D_FORTIFY_SOURCE=2
    -O3
)

set(DEBUG_FLAGS
    -g
    -O0
    -fverbose-asm
    -finstrument-functions
    -Xanalyzer
    -fno-inline
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(${RELEASE_FLAGS})
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(${DEBUG_FLAGS})
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++")
else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++")
endif()


add_subdirectory(utils)
add_subdirectory(day_1)
add_subdirectory(day_2)
# add_subdirectory(day_3)
