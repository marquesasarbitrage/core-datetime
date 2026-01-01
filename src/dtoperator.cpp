#include "../include/core-datetime/datetime.hpp"

DateTime DateTime::operator+(const TimeDelta& other) const {

    switch(type_){
        case EpochTimestampType::SECONDS: 
        {
            return DateTime(getTimestamp() + other.getTotalSeconds(), type_, timeZone_);
        }
        case EpochTimestampType::MILLISECONDS: 
        {
            return DateTime(getTimestamp() + other.getTotalMilliSeconds(), type_, timeZone_);
        }
        case EpochTimestampType::MICROSECONDS: 
        {
            return DateTime(getTimestamp() + other.getTotalMicroSeconds(), type_, timeZone_);
        }
        case EpochTimestampType::NANOSECONDS: 
        {
            return DateTime(getTimestamp() + other.getTotalNanoSeconds(), type_, timeZone_);
        }
    }
}

DateTime DateTime::operator-(const TimeDelta& other) const {

    switch(type_){
        case EpochTimestampType::SECONDS: 
        {
            return DateTime(getTimestamp() - other.getTotalSeconds(), type_, timeZone_);
        }
        case EpochTimestampType::MILLISECONDS: 
        {
            return DateTime(getTimestamp() - other.getTotalMilliSeconds(), type_, timeZone_);
        }
        case EpochTimestampType::MICROSECONDS: 
        {
            return DateTime(getTimestamp() - other.getTotalMicroSeconds(), type_, timeZone_);
        }
        case EpochTimestampType::NANOSECONDS: 
        {
            return DateTime(getTimestamp() - other.getTotalNanoSeconds(), type_, timeZone_);
        }
    }
}

TimeDelta DateTime::operator-(const DateTime& other) const {

    long long nanoseconds = getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp() - other.getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp();
    return TimeDelta(0,0,0,0,0,0,nanoseconds);

}

void DateTime::operator+=(const TimeDelta& other){ 
    tmsp_ = operator+(other).getTimestamp(); 
    civilTime_ = DatetimeToolbox::getCivilFromTimestamp(
        _getModifiedTimestamp(
            tmsp_
            , -static_cast<int>(timeZone_)
            , type_));
}

void DateTime::operator-=(const TimeDelta& other){ 
    tmsp_ = operator-(other).getTimestamp(); 
    civilTime_ = DatetimeToolbox::getCivilFromTimestamp(
        _getModifiedTimestamp(
            tmsp_
            , -static_cast<int>(timeZone_)
            , type_));
}

bool DateTime::operator==(const DateTime& other) const {
    if (getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()==other.getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()) return true;
    return false;
}

bool DateTime::operator<(const DateTime& other) const {
    if (getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()<other.getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()) return true;
    return false;
}

bool DateTime::operator<=(const DateTime& other) const {
    if (getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()<=other.getModifiedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()) return true;
    return false;
}

bool DateTime::operator!=(const DateTime& other) const { return operator==(other) ? false : true; } 

bool DateTime::operator>=(const DateTime& other) const { return operator<=(other) ? false : true; }

bool DateTime::operator>(const DateTime& other) const { return operator<(other) ? false : true; }

DateTime DateTime::operator+(const TimeDelta::Years& other) const {
 
    auto [y,m,d] = DatetimeToolbox::addYearsToCivilDate(
        std::get<0>(civilTime_)
        ,std::get<1>(civilTime_)
        ,std::get<2>(civilTime_)
        ,other.years_);
    TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
    return DateTime(y,m,d,timeZone_).getModifiedTimestampType(type_) + dt;
}

DateTime DateTime::operator-(const TimeDelta::Years& other) const {

    auto [y,m,d] = DatetimeToolbox::addYearsToCivilDate(
        std::get<0>(civilTime_)
        ,std::get<1>(civilTime_)
        ,std::get<2>(civilTime_)
        ,-other.years_);
    
    TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
    return DateTime(y,m,d,timeZone_).getModifiedTimestampType(type_) + dt;
}

DateTime DateTime::operator+(const TimeDelta::Months& other) const {
 
    auto [y,m,d] = DatetimeToolbox::addMonthsToCivilDate(
        std::get<0>(civilTime_)
        ,std::get<1>(civilTime_)
        ,std::get<2>(civilTime_)
        ,other.months_);
    TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
    return DateTime(y,m,d,timeZone_).getModifiedTimestampType(type_) + dt;
}

DateTime DateTime::operator-(const TimeDelta::Months& other) const {

    auto [y,m,d] = DatetimeToolbox::addMonthsToCivilDate(
        std::get<0>(civilTime_)
        ,std::get<1>(civilTime_)
        ,std::get<2>(civilTime_)
        ,-other.months_);

    TimeDelta dt = *this - DateTime(std::get<0>(civilTime_), std::get<1>(civilTime_), std::get<2>(civilTime_), timeZone_);
    return DateTime(y,m,d,timeZone_).getModifiedTimestampType(type_) + dt;
}

void DateTime::operator+=(const TimeDelta::Years& other){
    tmsp_ = operator+(other).getTimestamp(); 
    civilTime_ = DatetimeToolbox::getCivilFromTimestamp(
        _getModifiedTimestamp(
            tmsp_
            , -static_cast<int>(timeZone_)
            , type_));
    
}

void DateTime::operator-=(const TimeDelta::Years& other) {
    
    tmsp_ = operator-(other).getTimestamp(); 
    civilTime_ = DatetimeToolbox::getCivilFromTimestamp(
        _getModifiedTimestamp(
            tmsp_
            , -static_cast<int>(timeZone_)
            , type_));
}

void DateTime::operator+=(const TimeDelta::Months& other) {
    
    tmsp_ = operator+(other).getTimestamp(); 
    civilTime_ = DatetimeToolbox::getCivilFromTimestamp(
        _getModifiedTimestamp(
            tmsp_
            , -static_cast<int>(timeZone_)
            , type_));
}

void DateTime::operator-=(const TimeDelta::Months& other) {
    
    tmsp_ = operator-(other).getTimestamp(); 
    civilTime_ = DatetimeToolbox::getCivilFromTimestamp(
        _getModifiedTimestamp(
            tmsp_
            , -static_cast<int>(timeZone_)
            , type_));
}
