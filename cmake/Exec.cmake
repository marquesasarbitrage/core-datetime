add_executable(datetime-timedelta ${CMAKE_CURRENT_SOURCE_DIR}/tests/timedelta.cpp)
target_link_libraries(datetime-timedelta PUBLIC core-datetime)

add_executable(datetime-toolbox ${CMAKE_CURRENT_SOURCE_DIR}/tests/toolbox.cpp)
target_link_libraries(datetime-toolbox PUBLIC core-datetime)

add_executable(datetime-datetime ${CMAKE_CURRENT_SOURCE_DIR}/tests/datetime.cpp)
target_link_libraries(datetime-datetime PUBLIC core-datetime)

add_executable(datetime-sequence ${CMAKE_CURRENT_SOURCE_DIR}/tests/sequence.cpp)
target_link_libraries(datetime-sequence PUBLIC core-datetime)

add_executable(datetime-daycount ${CMAKE_CURRENT_SOURCE_DIR}/tests/daycountconvention.cpp)
target_link_libraries(datetime-daycount PUBLIC core-datetime)

add_executable(datetime-businessday ${CMAKE_CURRENT_SOURCE_DIR}/tests/businessday.cpp)
target_link_libraries(datetime-businessday PUBLIC core-datetime)