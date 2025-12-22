file(GLOB_RECURSE UTILS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_library(utils ${UTILS_SOURCES})

target_include_directories(utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
