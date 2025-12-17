#include <iostream>
#include "../include/core-datetime/datetime.hpp"

DateTime::DateTime(long long timestamp, EpochTimestampType type)
{
    if (timestamp<0) throw NegativeEpochTimestampError();
    setTimestamp(timestamp);
    setTimestampType(type);
};

DateTime::DateTime(){setTimestamp(std::time(nullptr)); setTimestampType(EpochTimestampType::SECONDS);}

long long DateTime::getTimestamp() const { return tmsp_; }

EpochTimestampType DateTime::getTimestampType() const{ return type_; }

std::tm DateTime::getCTimeObject() const {

    DateTime dt = getConvertedTimestampType(EpochTimestampType::SECONDS);
    std::time_t timestamp = dt.getTimestamp();
    std::tm* timeInfoPointer = std::localtime(&timestamp);
    return std::tm(*timeInfoPointer);
}

std::string DateTime::asString() {

    std::tm time_info = getCTimeObject();
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), str_format_.c_str(), &time_info);
    return std::string(buffer);
}

DateTime DateTime::getConvertedTimestampType(const EpochTimestampType type) const {

    return DateTime(round(double(static_cast<int>(type))/double(static_cast<int>(type_))*tmsp_),type);
}

void DateTime::setStringFormat(std::string format) { str_format_ = format; }

void DateTime::setTimestamp(const long long timestamp) { tmsp_ = timestamp; }

void DateTime::setTimestampType(const EpochTimestampType type) { type_ = type; }

void DateTime::convertTimestampType(const EpochTimestampType type)
{
    setTimestamp(double(static_cast<int>(type))/double(static_cast<int>(type_))*tmsp_); 
    setTimestampType(type);
}

DateTime DateTime::operator+(const TimeDelta& other) const {

    switch(type_){
        case EpochTimestampType::SECONDS: 
        {
            return DateTime(getTimestamp() + other.getTotalSeconds(), type_);
        }
        case EpochTimestampType::MILLISECONDS: 
        {
            return DateTime(getTimestamp() + other.getTotalMilliSeconds(), type_);
        }
        case EpochTimestampType::MICROSECONDS: 
        {
            return DateTime(getTimestamp() + other.getTotalMicroSeconds(), type_);
        }
        case EpochTimestampType::NANOSECONDS: 
        {
            return DateTime(getTimestamp() + other.getTotalNanoSeconds(), type_);
        }
    }
}

DateTime DateTime::operator-(const TimeDelta& other) const {

    switch(type_){
        case EpochTimestampType::SECONDS: 
        {
            return DateTime(getTimestamp() - other.getTotalSeconds(), type_);
        }
        case EpochTimestampType::MILLISECONDS: 
        {
            return DateTime(getTimestamp() - other.getTotalMilliSeconds(), type_);
        }
        case EpochTimestampType::MICROSECONDS: 
        {
            return DateTime(getTimestamp() - other.getTotalMicroSeconds(), type_);
        }
        case EpochTimestampType::NANOSECONDS: 
        {
            return DateTime(getTimestamp() - other.getTotalNanoSeconds(), type_);
        }
    }
}

TimeDelta DateTime::operator-(const DateTime& other) const {

    long long nanoseconds = getConvertedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp() - other.getConvertedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp();
    return TimeDelta(0,0,0,0,0,0,nanoseconds);

}

void DateTime::operator+=(const TimeDelta& other){ setTimestamp(operator+(other).getTimestamp()); }

void DateTime::operator-=(const TimeDelta& other){ setTimestamp(operator-(other).getTimestamp()); }

bool DateTime::operator==(const DateTime& other) const {
    if (getConvertedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()==other.getConvertedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()) return true;
    return false;
}

bool DateTime::operator<(const DateTime& other) const {
    if (getConvertedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()<other.getConvertedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()) return true;
    return false;
}

bool DateTime::operator<=(const DateTime& other) const {
    if (getConvertedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()<=other.getConvertedTimestampType(EpochTimestampType::NANOSECONDS).getTimestamp()) return true;
    return false;
}

bool DateTime::operator!=(const DateTime& other) const { return operator==(other) ? false : true; } 

bool DateTime::operator>=(const DateTime& other) const { return operator<=(other) ? false : true; }

bool DateTime::operator>(const DateTime& other) const { return operator<(other) ? false : true; }

