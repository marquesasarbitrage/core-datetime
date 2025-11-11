add_library(core-datetime 
    STATIC 
        src/datetime.cpp
        src/timedelta.cpp
        src/errors.cpp
        src/tools.cpp)

target_include_directories(core-datetime PUBLIC include)