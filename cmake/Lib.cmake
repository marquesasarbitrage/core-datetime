add_library(core-datetime 
    STATIC 
        src/timedelta.cpp
        src/toolbox.cpp
        src/errors.cpp
        src/dtconstructor.cpp
        src/dtoperator.cpp
        src/dtfunctions.cpp
        src/sequence.cpp
        src/daycountconvention.cpp
        src/businessday.cpp)

target_include_directories(core-datetime PUBLIC include)