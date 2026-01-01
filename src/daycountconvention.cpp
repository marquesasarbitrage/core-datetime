#include "../include/core-datetime/daycountconvention.hpp"

double YearFractionCalculator::get(const DateTime& startDate, const DateTime& endDate, DayCountConvention dayCountConvention) {

    if (startDate>endDate) throw DatetimeErrorRegistry::InvalidStartEndDate();
    switch (dayCountConvention)
    {

        case DayCountConvention::ACTUAL_360: return YearFractionCalculator::getAct360(startDate,endDate);
        case DayCountConvention::ACTUAL_365: return YearFractionCalculator::getAct365(startDate,endDate);
        case DayCountConvention::ACTUAL_364: return YearFractionCalculator::getAct364(startDate,endDate);
        case DayCountConvention::ACTUAL_ACTUAL: return YearFractionCalculator::getActAct(startDate,endDate);
        case DayCountConvention::BOND_BASIS30_360: return YearFractionCalculator::getBondBasis30_360(startDate,endDate);
        case DayCountConvention::E30_360: return YearFractionCalculator::getE30_360(startDate,endDate);
        default: throw DatetimeErrorRegistry::UnknownDayCountConventionError();

    }
}

double YearFractionCalculator::getAct360(const DateTime& startDate, const DateTime& endDate) {

    return double((endDate-startDate).getTotalNanoSeconds())/YearFractionCalculator::FACTOR360;
}

double YearFractionCalculator::getAct365(const DateTime& startDate, const DateTime& endDate){

    return double((endDate-startDate).getTotalNanoSeconds())/YearFractionCalculator::FACTOR365;
}

double YearFractionCalculator::getAct364(const DateTime& startDate, const DateTime& endDate) {

    return double((endDate-startDate).getTotalNanoSeconds())/YearFractionCalculator::FACTOR364;
}

double YearFractionCalculator::getActAct(const DateTime& startDate, const DateTime& endDate) {

    long long leap = double(YearFractionCalculator::getTimeInLeapYears(startDate, endDate).getTotalNanoSeconds());
    long long total = double((endDate-startDate).getTotalNanoSeconds()); 
    return double(leap)/YearFractionCalculator::FACTOR366 + double(total-leap)/YearFractionCalculator::FACTOR365;
}

double YearFractionCalculator::getE30_360(const DateTime& startDate, const DateTime& endDate) {

    int d2 = endDate.getDay(), d1 = startDate.getDay(); 
    return (get30360BaseCount(startDate,endDate) + (std::min(30,d2)-std::min(30,d1)))/360.0;
}

double YearFractionCalculator::getBondBasis30_360(const DateTime& startDate, const DateTime& endDate) {

    int d2 = endDate.getDay(), d1 = startDate.getDay(); 
    d1 = std::min(30,d1);
    d2 = (d1==30) ? std::min(30,d2) : d2;
    return (get30360BaseCount(startDate,endDate) + (d2-d1))/360.0;
}

double YearFractionCalculator::get30360BaseCount(const DateTime& startDate, const DateTime& endDate) {

    return 360.0*(endDate.getYear()-startDate.getYear()) + 30.0*(endDate.getMonth()-startDate.getMonth());
}

TimeDelta YearFractionCalculator::getTimeInLeapYears(const DateTime& startDate, const DateTime& endDate) {

    int endYear = endDate.getYear(), startYear = startDate.getYear();
    TimeDelta result(0,0,0,0,0,0,0);
    if (endYear == startYear) { 
        if (DatetimeToolbox::isLeapYear(endYear)) result = endDate - startDate; 
    } else {
        for (int y = startYear; y<=endYear; y++) {

            if (!DatetimeToolbox::isLeapYear(y)) continue ; 
            
            if (y == startYear) {

                result += DateTime(startYear+1,1,1,startDate.getTimeZone())-startDate;

            } else if (y == endYear) {

                result += endDate - DateTime(endYear,1,1,startDate.getTimeZone());

            } else {

                result += TimeDelta(366,0,0,0,0,0,0);
            }
        }
    }
    
    return result;
}