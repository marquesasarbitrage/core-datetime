add_library(cpp-datetime 
    STATIC 
        src/datetime.cpp
        src/timedelta.cpp
        src/errors.cpp
        src/tools.cpp)

target_include_directories(cpp-datetime PUBLIC include)