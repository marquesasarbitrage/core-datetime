#pragma once
#include <iostream>
#include <tuple>
#include "errors.hpp"

namespace DatetimeToolbox {

    static constexpr double dayInNanoSeconds = 1000000000.0*24.0*60.0*60.0;

    static constexpr int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    void checkCivilDate(int year, int month, int day); 

    void checkCivilHour(int hour, int minute, int second); 

    bool isLeapYear(int year);

    long long getDaysSinceEpoch(int year, int month, int day);

    long long getTimestampFromCivilDateHour(int year, int month, int day, int hour, int minute, int second);

    long long getTimestampFromCivilDateHourString(std::string dateString, std::string dateFormat); 

    std::tuple<int, int, int, int, int, int> getCivilFromTimestamp(long long tmsp);

    std::string getCivilDateHourStringFromCivilDateHour(int year, int month, int day, int hour, int minute, int second, std::string dateFormat);

    std::string getCivilDateHourStringFromTimestamp(long long tmsp, std::string dateFormat);

    int getWeekDayFromTimestamp(long long tmsp);

    int getWeekDayFromCivilDate(int year, int month, int day);

    int getFirstWeekDayOfMonth(int year, int month, int weekDay);

    int getSecondWeekDayOfMonth(int year, int month, int weekDay);

    int getThirdWeekDayOfMonth(int year, int month, int weekDay);

    int getFourthWeekDayOfMonth(int year, int month, int weekDay);

    int getLastWeekDayOfMonth(int year, int month, int weekDay);

    long long nowNanoSeconds();

    bool isEndMonth(int year, int month, int day);

    int getDaysInMonth(int year, int month);

    std::tuple<int, int, int> addYearsToCivilDate(int year, int month, int day, int n);

    std::tuple<int, int, int> addMonthsToCivilDate(int year, int month, int day, int n);
}