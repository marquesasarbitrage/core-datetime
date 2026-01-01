#pragma once 
#include <iostream>
#include "datetime.hpp"
#include "sequence.hpp"

enum class BusinessDayConvention {
    FOLLOWING, 
    PRECEDING, 
    MODIFIED_FOLLOWING, 
    MODIFIED_PRECEDING
};

enum class HolidayCalendar {
    NONE, 
    WEEK_END_OFF,
    US_FEDERAL_RESERVE
};

class BusinessDay {

    public: 
        static bool isWeekEnd(const DateTime& date);
        static bool isChristmas(const DateTime& date); 
        static bool isNewYear(const DateTime& date);
        static bool isMartinLutterKingDay(const DateTime& date);
        static bool isUSWashingtonBirthday(const DateTime& date);
        static bool isUSMemorialDay(const DateTime& date);
        static bool isUSJuneteenth(const DateTime& date);
        static bool isUSIndependanceDay(const DateTime& date);
        static bool isUSLaborDay(const DateTime& date);
        static bool isUSColumbusDay(const DateTime& date);
        static bool isUSVeteransDay(const DateTime& date);
        static bool isThanksgivingDay(const DateTime& date);

        static bool isBusiness(const DateTime& date, HolidayCalendar holidayCalendar); 
        static DateTime getAdjustedDate(const DateTime& date, HolidayCalendar holidayCalendar, BusinessDayConvention businessDayConvention); 
        static DatetimeSequence getAdjustedDateSequence(const DatetimeSequence& sequence, HolidayCalendar holidayCalendar, BusinessDayConvention businessDayConvention);

    private: 
        static bool isUSFederalReserveBusiness(const DateTime& date);

        static DateTime getAdjustedDateFollowing(const DateTime& date, HolidayCalendar holidayCalendar);
        static DateTime getAdjustedDatePreceding(const DateTime& date, HolidayCalendar holidayCalendar);
        static DateTime getAdjustedDateModPreceding(const DateTime& date, HolidayCalendar holidayCalendar);
        static DateTime getAdjustedDateModFollowing(const DateTime& date, HolidayCalendar holidayCalendar);

};