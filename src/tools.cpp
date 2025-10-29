#include <iostream>
#include "../include/cpp-datetime/tools.hpp"

namespace DateTimeTools {

    bool isWeekEnd(const DateTime& date) {return date.getCTimeObject().tm_wday == 0 ? true : date.getCTimeObject().tm_wday == 6 ? true : false;}

    bool isEndMonth(const DateTime& date)
    {
        std::tm t = date.getCTimeObject();
        int year = getYear(date); 
        int lastDay = daysInMonth[t.tm_mon];
        if (t.tm_mon == 1 and isLeapYear(year)) lastDay = 29;
        return t.tm_mday == lastDay;
    }

    int getYear(const DateTime& date) {return date.getCTimeObject().tm_year + 1900;}

    bool isLeapYear(const DateTime& date){return isLeapYear(date.getCTimeObject().tm_year + 1900);}

    bool isLeapYear(int year){return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));}
    
    TimeDelta getTimeInLeapYear(const DateTime& startDate, const DateTime& endDate)
    {
        int endYear = getYear(endDate);
        int startYear = getYear(startDate);
        int yearDiff = endYear - startYear;
        TimeDelta output = TimeDelta(0,0,0,0,0,0,0);
        if (yearDiff == 0 && isLeapYear(endDate)) output += endDate-startDate;
        else 
        {
            for (int i = 1; i<=yearDiff; i++)
            {
                startYear += 1; 
                if (isLeapYear(startYear)) 
                {
                    if (i == yearDiff) output += endDate - getYearBeginningDate(endDate);
                    else output += TimeDelta(366,0,0,0,0,0,0); 
                    
                } else output += TimeDelta(0,0,0,0,0,0,0);
            }
        }
        return output;
    }
    
    DateTime getMidnightDateTime(const DateTime& date)
    {
        std::time_t timestamp = date.getConvertedTimestampType(EpochTimestampType::SECONDS).getTimestamp();
        std::tm* local_tm = std::gmtime(&timestamp);
        local_tm->tm_hour = 0;
        local_tm->tm_min  = 0;
        local_tm->tm_sec  = 0;
        return DateTime(static_cast<long long>(timegm(local_tm)), EpochTimestampType::SECONDS);
    }

    DateTime getYearBeginningDate(const DateTime& date)
    {
        std::time_t timestamp = date.getConvertedTimestampType(EpochTimestampType::SECONDS).getTimestamp();
        std::tm* local_tm = std::gmtime(&timestamp);
        local_tm->tm_hour = 0;
        local_tm->tm_min  = 0;
        local_tm->tm_sec  = 0;
        local_tm->tm_mday = 1; 
        local_tm->tm_mon = 0; 
        long long timestampAsLong = static_cast<long long>(timegm(local_tm)); 
        return DateTime(timestampAsLong, EpochTimestampType::SECONDS);
    }
    
};