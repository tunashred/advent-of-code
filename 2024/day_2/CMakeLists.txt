set(TARGET_PART_1 "day_2_part_1")
set(TARGET_PART_2 "day_2_part_2")

add_executable(${TARGET_PART_1} part_1.cpp)
add_executable(${TARGET_PART_2} part_2.cpp)

target_link_libraries(${TARGET_PART_1} PUBLIC utils_lib)
target_link_libraries(${TARGET_PART_2} PUBLIC utils_lib)
