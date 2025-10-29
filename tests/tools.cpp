#include <iostream>
#include <cassert>
#include "../include/cpp-datetime/tools.hpp"

int main()
{
    // Friday 31 October 2025 00:00:00
    DateTime date1 = DateTime(1761868800, EpochTimestampType::SECONDS); 

    assert(DateTimeTools::isWeekEnd(date1)==false); 
    assert(DateTimeTools::isWeekEnd(date1+TimeDelta(1,0,0,0,0,0,0))==true); 

    assert(DateTimeTools::isEndMonth(date1)==true); 
    assert(DateTimeTools::isEndMonth(date1-TimeDelta(1,0,0,0,0,0,0))==false);

    assert(DateTimeTools::getYear(date1)==2025);

    assert(DateTimeTools::isLeapYear(2025)==false);
    assert(DateTimeTools::isLeapYear(2028)==true);
    assert(DateTimeTools::isLeapYear(date1)==false);
    assert(DateTimeTools::isLeapYear(date1+TimeDelta(365*3,0,0,0,0,0,0))==true);

    assert(DateTimeTools::getMidnightDateTime(date1 + TimeDelta(0,8,0,0,0,0,0))==date1); 
    assert(DateTimeTools::getYearBeginningDate(date1)==DateTime(1735689600,EpochTimestampType::SECONDS)); 

    // 25 Août 2025 21:00:00 
    DateTime referenceTime = DateTime(1756155600,EpochTimestampType::SECONDS); 
    // 14 Novembre 2026 21:00:00 
    DateTime d2 = DateTime(1794690000,EpochTimestampType::SECONDS); 
    // 18 Mai 2027 21:00:00 
    DateTime d3 = DateTime(1810674000,EpochTimestampType::SECONDS); 
    // 31 Octobre 2028 21:00:00 
    DateTime d4 = DateTime(1856638800,EpochTimestampType::SECONDS); 
    // 30 Septemmbre 2029 21:00:00 
    DateTime d5 = DateTime(1885496400,EpochTimestampType::SECONDS);

    assert(DateTimeTools::getTimeInLeapYear(referenceTime,d2) == TimeDelta(0,0,0,0,0,0,0)); 
    assert(DateTimeTools::getTimeInLeapYear(referenceTime,d3) == TimeDelta(0,0,0,0,0,0,0)); 
    assert(DateTimeTools::getTimeInLeapYear(referenceTime,d5) == TimeDelta(366,0,0,0,0,0,0)); 
    assert(DateTimeTools::getTimeInLeapYear(referenceTime,d4) == TimeDelta(304,21,0,0,0,0,0)); 
    
    std::cout << "All datetime tool tests has passed." << std::endl; 
    return 0; 
}