# tests DateTime and TimeDelta
add_executable(datetime-datetime ${CMAKE_CURRENT_SOURCE_DIR}/tests/datetime.cpp)
target_link_libraries(datetime-datetime PUBLIC core-datetime)

add_executable(datetime-tools ${CMAKE_CURRENT_SOURCE_DIR}/tests/tools.cpp)
target_link_libraries(datetime-tools PUBLIC core-datetime)