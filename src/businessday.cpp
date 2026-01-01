#include "../include/core-datetime/businessday.hpp"

bool BusinessDay::isBusiness(const DateTime& date, HolidayCalendar holidayCalendar) {

    switch (holidayCalendar)
    {
        case HolidayCalendar::NONE : return true;
        case HolidayCalendar::WEEK_END_OFF : return !isWeekEnd(date);
        case HolidayCalendar::US_FEDERAL_RESERVE: return isUSFederalReserveBusiness(date);
        default: throw DatetimeErrorRegistry::UnknownHolidayCalendarError();
    }
}

DateTime BusinessDay::getAdjustedDateFollowing(const DateTime& date, HolidayCalendar holidayCalendar) {

    DateTime newDate = date;
    while (!isBusiness(newDate,holidayCalendar)) { newDate += TimeDelta(1,0,0,0,0,0,0); }
    return newDate;
}

DateTime BusinessDay::getAdjustedDatePreceding(const DateTime& date, HolidayCalendar holidayCalendar) {

    DateTime newDate = date;
    while (!isBusiness(newDate,holidayCalendar)) { newDate -= TimeDelta(1,0,0,0,0,0,0); }
    return newDate;
}

DateTime BusinessDay::getAdjustedDateModPreceding(const DateTime& date, HolidayCalendar holidayCalendar) {

    DateTime modPrec = getAdjustedDatePreceding(date, holidayCalendar); 
    if (modPrec.getMonth()== date.getMonth()) return modPrec; 
    else return getAdjustedDateFollowing(date, holidayCalendar);
}

DateTime BusinessDay::getAdjustedDateModFollowing(const DateTime& date, HolidayCalendar holidayCalendar) {

    DateTime modFol = getAdjustedDateFollowing(date, holidayCalendar); 
    if (modFol.getMonth() == date.getMonth()) return modFol; 
    else return getAdjustedDatePreceding(date, holidayCalendar);
}

DateTime BusinessDay::getAdjustedDate(const DateTime& date, HolidayCalendar holidayCalendar, BusinessDayConvention businessDayConvention) {

    switch (businessDayConvention)
    {
        case BusinessDayConvention::FOLLOWING: return getAdjustedDateFollowing(date, holidayCalendar);
        case BusinessDayConvention::PRECEDING: return getAdjustedDatePreceding(date, holidayCalendar);
        case BusinessDayConvention::MODIFIED_FOLLOWING: return getAdjustedDateModFollowing(date, holidayCalendar);
        case BusinessDayConvention::MODIFIED_PRECEDING: return getAdjustedDateModPreceding(date, holidayCalendar);
        default: throw DatetimeErrorRegistry::UnknownBusinessDayConventionError();
    }
}

DatetimeSequence BusinessDay::getAdjustedDateSequence(const DatetimeSequence& sequence, HolidayCalendar holidayCalendar, BusinessDayConvention businessDayConvention) {

    std::set<DateTime> initialSet = sequence.get(); 
    std::set<DateTime> finalSet; 
    for (DateTime s : initialSet) { finalSet.insert(getAdjustedDate(s, holidayCalendar, businessDayConvention));}
    return DatetimeSequence(finalSet);
}

bool BusinessDay::isWeekEnd(const DateTime& date) {

    int wk = DatetimeToolbox::getWeekDayFromCivilDate(date.getYear(),date.getMonth(),date.getDay()); 
    return (wk==6 or wk==0) ? true : false;
}

bool BusinessDay::isChristmas(const DateTime& date) { return (date.getDay()==25 && date.getMonth()==12); }

bool BusinessDay::isNewYear(const DateTime& date) { return (date.getDay()==1 && date.getMonth()==1); }

bool BusinessDay::isMartinLutterKingDay(const DateTime& date) {

    int y = date.getYear(), m = date.getMonth(), d = date.getDay();
    if (m != 1) return false;
    if (DatetimeToolbox::getWeekDayFromCivilDate(y,m,d) == 1) return DatetimeToolbox::getThirdWeekDayOfMonth(y,m,1)==d;
    else return false;
}

bool BusinessDay::isUSWashingtonBirthday(const DateTime& date) {

    int y = date.getYear(), m = date.getMonth(), d = date.getDay();
    if (m != 2) return false;
    if (DatetimeToolbox::getWeekDayFromCivilDate(y,m,d) == 1) return DatetimeToolbox::getThirdWeekDayOfMonth(y,m,1)==d;
    else return false;
}

bool BusinessDay::isUSMemorialDay(const DateTime& date) {

    int y = date.getYear(), m = date.getMonth(), d = date.getDay();
    if (m != 5) return false;
    if (DatetimeToolbox::getWeekDayFromCivilDate(y,m,d) == 1) return DatetimeToolbox::getLastWeekDayOfMonth(y,m,1)==d;
    else return false;
}

bool BusinessDay::isUSJuneteenth(const DateTime& date) {

    return (date.getDay()==19 && date.getMonth()==6);
}

bool BusinessDay::isUSIndependanceDay(const DateTime& date) {

    return (date.getDay()==4 && date.getMonth()==7);
}

bool BusinessDay::isUSLaborDay(const DateTime& date) {

    int y = date.getYear(), m = date.getMonth(), d = date.getDay();
    if (m != 9) return false;
    if (DatetimeToolbox::getWeekDayFromCivilDate(y,m,d) == 1) return DatetimeToolbox::getFirstWeekDayOfMonth(y,m,1)==d;
    else return false;
}

bool BusinessDay::isUSColumbusDay(const DateTime& date) {

    int y = date.getYear(), m = date.getMonth(), d = date.getDay();
    if (m != 10) return false;
    if (DatetimeToolbox::getWeekDayFromCivilDate(y,m,d) == 1) return DatetimeToolbox::getSecondWeekDayOfMonth(y,m,1)==d;
    else return false;
}

bool BusinessDay::isUSVeteransDay(const DateTime& date) {

    return (date.getDay()==11 && date.getMonth()==11);
}

bool BusinessDay::isThanksgivingDay(const DateTime& date) {

    int y = date.getYear(), m = date.getMonth(), d = date.getDay();
    if (m != 11) return false;
    if (DatetimeToolbox::getWeekDayFromCivilDate(y,m,d) == 4) return DatetimeToolbox::getFourthWeekDayOfMonth(y,m,4)==d;
    else return false;
}

bool BusinessDay::isUSFederalReserveBusiness(const DateTime& date) {

    int m = date.getMonth(); 
    int wk = DatetimeToolbox::getWeekDayFromCivilDate(date.getYear(),m,date.getDay());
    if (wk==6 or wk==0) return false; 
    if (m == 3 or m == 8 or m == 4) return true; 

    if (isChristmas(date)) return false; 
    if (isUSJuneteenth(date)) return false; 
    if (isNewYear(date)) return false; 
    if (isUSIndependanceDay(date)) return false; 
    if (isUSVeteransDay(date)) return false; 

    if (wk==1) {

        if (m==1) { if (isMartinLutterKingDay(date)) return false;}
        if (m==2) { if (isUSWashingtonBirthday(date)) return false;} 
        if (m==5) { if (isUSMemorialDay(date)) return false;} 
        if (m==9) { if (isUSLaborDay(date)) return false;} 
        if (m==10) { if (isUSColumbusDay(date)) return false;} 

    } else if (wk == 4) { if (isThanksgivingDay(date)) return false; }
    else return true;
    return true;
}