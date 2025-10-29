# tests DateTime and TimeDelta
add_executable(datetime-datetime ${CMAKE_CURRENT_SOURCE_DIR}/tests/datetime.cpp)
target_link_libraries(datetime-datetime PUBLIC cpp-datetime)

add_executable(datetime-tools ${CMAKE_CURRENT_SOURCE_DIR}/tests/tools.cpp)
target_link_libraries(datetime-tools PUBLIC cpp-datetime)