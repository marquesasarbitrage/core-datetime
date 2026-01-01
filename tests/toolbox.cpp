#include <iostream>
#include <cassert>
#include "../include/core-datetime/toolbox.hpp"

void testCheck() {

    DatetimeToolbox::checkCivilDate(2025,10,12); 

    try { DatetimeToolbox::checkCivilDate(2025,13,12); assert(false);} 
    catch (const DatetimeErrorRegistry::InvalidCivilDateError& e) { assert(true); }

    try { DatetimeToolbox::checkCivilHour(25,30,30); assert(false);} 
    catch (const DatetimeErrorRegistry::InvalidCivilHourError& e) { assert(true); }

    DatetimeToolbox::checkCivilHour(23,30,30);
    DatetimeToolbox::checkCivilHour(0,1,12);
    DatetimeToolbox::checkCivilHour(0,0,12);
    DatetimeToolbox::checkCivilHour(0,0,0);

    try { DatetimeToolbox::checkCivilDate(0,0,12); assert(false);} 
    catch (const DatetimeErrorRegistry::InvalidCivilDateError& e) { assert(true); }
}

void testIsLeap() {

    assert(DatetimeToolbox::isLeapYear(2024)); 
    assert(!DatetimeToolbox::isLeapYear(2023)); 
}

void testDaysSinceEpoch() {

    assert(DatetimeToolbox::getDaysSinceEpoch(1800,1,1)==-62091); 
    assert(DatetimeToolbox::getDaysSinceEpoch(2025,7,18)==20287); 
    assert(DatetimeToolbox::getDaysSinceEpoch(2000,12,12)==11303); 
}

void testCivilToTimestamp() {

    assert(DatetimeToolbox::getTimestampFromCivilDateHour(1800,12,28,16,28,40)==-5333412680); 
    assert(DatetimeToolbox::getTimestampFromCivilDateHour(2025,12,28,16,28,40)==1766939320);
    assert(DatetimeToolbox::getTimestampFromCivilDateHour(2000,12,28,0,0,0)==977961600);  
}

void testTimestampToCivil() {

    assert(DatetimeToolbox::getCivilFromTimestamp(-5333412680) == std::make_tuple(1800,12,28,16,28,40)); 
    assert(DatetimeToolbox::getCivilFromTimestamp(1766939320) == std::make_tuple(2025,12,28,16,28,40)); 
    assert(DatetimeToolbox::getCivilFromTimestamp(977961600) == std::make_tuple(2000,12,28,0,0,0)); 
}

void testStringToTimestammp() {

    assert(DatetimeToolbox::getTimestampFromCivilDateHourString("2025-12-28 16:28:40", "YYYY-MM-DD HH:MM:SS")==1766939320);
    assert(DatetimeToolbox::getTimestampFromCivilDateHourString("2000-12-28", "YYYY-MM-DD")==977961600); 
}

void testTimestampToString() {

    assert(DatetimeToolbox::getCivilDateHourStringFromTimestamp(1766939320, "YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40");
    assert(DatetimeToolbox::getCivilDateHourStringFromTimestamp(977961600, "YYYY-MM-DD")=="2000-12-28"); 

}

void testWeekDayFromTimestamp() {
    assert(DatetimeToolbox::getWeekDayFromTimestamp(977961600)==4); 
    assert(DatetimeToolbox::getWeekDayFromTimestamp(978134400)==6); 
    assert(DatetimeToolbox::getWeekDayFromTimestamp(977702400)==1); 
}

void testWeekDayFromCivilDate() {
    assert(DatetimeToolbox::getWeekDayFromCivilDate(2000,12,28)==4); 
    assert(DatetimeToolbox::getWeekDayFromCivilDate(2000,12,30)==6); 
    assert(DatetimeToolbox::getWeekDayFromCivilDate(2000,12,25)==1); 
}

void testNthWeekDayInMonth() {

    assert(DatetimeToolbox::getFirstWeekDayOfMonth(2025,9,2)==2); 
    assert(DatetimeToolbox::getSecondWeekDayOfMonth(2025,9,2)==9); 
    assert(DatetimeToolbox::getThirdWeekDayOfMonth(2025,9,2)==16); 
    assert(DatetimeToolbox::getFourthWeekDayOfMonth(2025,9,2)==23); 
    assert(DatetimeToolbox::getLastWeekDayOfMonth(2025,9,2)==30); 

    assert(DatetimeToolbox::getFirstWeekDayOfMonth(2025,9,3)==3); 
    assert(DatetimeToolbox::getSecondWeekDayOfMonth(2025,9,3)==10); 
    assert(DatetimeToolbox::getThirdWeekDayOfMonth(2025,9,3)==17); 
    assert(DatetimeToolbox::getFourthWeekDayOfMonth(2025,9,3)==24); 
    assert(DatetimeToolbox::getLastWeekDayOfMonth(2025,9,3)==24); 

    assert(DatetimeToolbox::getFirstWeekDayOfMonth(2025,9,1)==1); 
    assert(DatetimeToolbox::getSecondWeekDayOfMonth(2025,9,1)==8); 
    assert(DatetimeToolbox::getThirdWeekDayOfMonth(2025,9,1)==15); 
    assert(DatetimeToolbox::getFourthWeekDayOfMonth(2025,9,1)==22); 
    assert(DatetimeToolbox::getLastWeekDayOfMonth(2025,9,1)==29); 
}

void testAddYears() {

    assert(DatetimeToolbox::addYearsToCivilDate(2025,3,15,3)==std::make_tuple(2028,3,15)); 
    assert(DatetimeToolbox::addYearsToCivilDate(2025,3,15,-3)==std::make_tuple(2022,3,15)); 
    assert(DatetimeToolbox::addYearsToCivilDate(2024,2,29,1)==std::make_tuple(2025,2,28)); 
    assert(DatetimeToolbox::addYearsToCivilDate(2024,2,29,-1)==std::make_tuple(2023,2,28)); 
    assert(DatetimeToolbox::addYearsToCivilDate(1997,8,15,28)==std::make_tuple(2025,8,15)); 
    assert(DatetimeToolbox::addYearsToCivilDate(2025,8,15,-28)==std::make_tuple(1997,8,15)); 
}

void testAddMonths() {

    assert(DatetimeToolbox::addMonthsToCivilDate(2025,12,29,2)==std::make_tuple(2026,2,28)); 
    assert(DatetimeToolbox::addMonthsToCivilDate(2025,12,29,26)==std::make_tuple(2028,2,29)); 
    assert(DatetimeToolbox::addMonthsToCivilDate(2025,3,2,4)==std::make_tuple(2025,7,2)); 
    assert(DatetimeToolbox::addMonthsToCivilDate(2025,3,2,12)==std::make_tuple(2026,3,2)); 
    
    assert(DatetimeToolbox::addMonthsToCivilDate(2026,3,1,-2)==std::make_tuple(2026,1,1)); 
    assert(DatetimeToolbox::addMonthsToCivilDate(2028,2,29,-26)==std::make_tuple(2025,12,29)); 
    assert(DatetimeToolbox::addMonthsToCivilDate(2025,7,2,-4)==std::make_tuple(2025,3,2)); 
    assert(DatetimeToolbox::addMonthsToCivilDate(2026,3,2,-12)==std::make_tuple(2025,3,2)); 
}

void testConsistencyAddMonthYear() {

    assert(DatetimeToolbox::addYearsToCivilDate(2025,3,15,3)==DatetimeToolbox::addMonthsToCivilDate(2025,3,15,3*12)); 
    assert(DatetimeToolbox::addYearsToCivilDate(2025,3,15,-3)==DatetimeToolbox::addMonthsToCivilDate(2025,3,15,-3*12)); 
    assert(DatetimeToolbox::addYearsToCivilDate(2025,3,15,-1)==DatetimeToolbox::addMonthsToCivilDate(2025,3,15,-1*12)); 
    assert(DatetimeToolbox::addYearsToCivilDate(2025,3,15,1)==DatetimeToolbox::addMonthsToCivilDate(2025,3,15,1*12)); 
}

int main() {

    testCheck();
    testIsLeap();
    testDaysSinceEpoch();
    testTimestampToCivil();
    testCivilToTimestamp();
    testStringToTimestammp();
    testTimestampToString();
    testWeekDayFromTimestamp();
    testWeekDayFromCivilDate();
    testNthWeekDayInMonth();
    testAddYears();
    testAddMonths();
    testConsistencyAddMonthYear();
    std::cout << "All toolbox tests has been passed !" << std::endl; 
    return 0;
}