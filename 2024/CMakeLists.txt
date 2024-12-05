cmake_minimum_required(VERSION 3.0.0)

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name and version
project(advent_of_code_2024 VERSION 0.1.0 LANGUAGES C CXX)

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
)

# Release specific flags
set(RELEASE_FLAGS
    -D_FORTIFY_SOURCE=2
    -O3
)

# Debug specific flags
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

add_subdirectory(utils)
add_subdirectory(day_1)
