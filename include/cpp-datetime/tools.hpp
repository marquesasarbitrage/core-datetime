#pragma once 
#include <iostream>
#include "datetime.hpp"

namespace DateTimeTools {
    static constexpr double dayInNanoSeconds = static_cast<double>(EpochTimestampType::NANOSECONDS)*24.0*60.0*60.0;
    static constexpr int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int getYear(const DateTime& date); 
    bool isWeekEnd(const DateTime& date);
    bool isEndMonth(const DateTime& date);
    bool isLeapYear(int year);
    bool isLeapYear(const DateTime& date);
    TimeDelta getTimeInLeapYear(const DateTime& startDate, const DateTime& endDate);
    DateTime getMidnightDateTime(const DateTime& date);
    DateTime getYearBeginningDate(const DateTime& date);
};

