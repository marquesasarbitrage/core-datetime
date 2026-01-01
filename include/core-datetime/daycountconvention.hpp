#pragma once 
#include <iostream>
#include "datetime.hpp"

enum class DayCountConvention {

    ACTUAL_360, 
    ACTUAL_365, 
    ACTUAL_364, 
    ACTUAL_ACTUAL, 
    E30_360, 
    BOND_BASIS30_360
};

class YearFractionCalculator {

    public: 
        static double get(const DateTime& startDate, const DateTime& endDate, DayCountConvention dayCountConvention); 
    
    private:
        static constexpr double FACTOR365 = 365.0*DatetimeToolbox::dayInNanoSeconds;
        static constexpr double FACTOR366 = 366.0*DatetimeToolbox::dayInNanoSeconds;
        static constexpr double FACTOR364 = 364.0*DatetimeToolbox::dayInNanoSeconds;
        static constexpr double FACTOR360 = 360.0*DatetimeToolbox::dayInNanoSeconds;
        
        static double getAct360(const DateTime& startDate, const DateTime& endDate); 
        static double getAct365(const DateTime& startDate, const DateTime& endDate); 
        static double getAct364(const DateTime& startDate, const DateTime& endDate); 
        static double getActAct(const DateTime& startDate, const DateTime& endDate); 
        static double getE30_360(const DateTime& startDate, const DateTime& endDate); 
        static double getBondBasis30_360(const DateTime& startDate, const DateTime& endDate); 

        static double get30360BaseCount(const DateTime& startDate, const DateTime& endDate);
        static TimeDelta getTimeInLeapYears(const DateTime& startDate, const DateTime& endDate);
};
