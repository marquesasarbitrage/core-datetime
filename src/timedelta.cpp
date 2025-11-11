#include <iostream>
#include "../include/core-datetime/datetime.hpp"

TimeDelta::TimeDelta(long long days, long long hours, long long minutes, long long seconds, 
    long long milliseconds, long long microseconds, long long nanoseconds)
    {days_ = days; hours_ = hours; minutes_ = minutes; seconds_ = seconds; milliseconds_ = milliseconds; microseconds_ = microseconds;nanoseconds_ = nanoseconds;};
TimeDelta::TimeDelta():days_(0), hours_(0), minutes_(0), seconds_(0), milliseconds_(0), microseconds_(0), nanoseconds_(0){};

void TimeDelta::setDays(long long n) {days_ = n;};
void TimeDelta::setHours(long long n) {hours_ = n;};
void TimeDelta::setMinutes(long long n) {minutes_ = n;};
void TimeDelta::setSeconds(long long n) {seconds_ = n;};
void TimeDelta::setMicroseconds(long long n) {microseconds_ = n;};
void TimeDelta::setMilliseconds(long long n) {milliseconds_ = n;};
void TimeDelta::setNanoseconds(long long n) {nanoseconds_ = n;}; 
TimeDelta TimeDelta::operator+(const TimeDelta& other) const {return TimeDelta(0,0,0,0,0,0,getTotalNanoSeconds()+other.getTotalNanoSeconds());};
TimeDelta TimeDelta::operator-(const TimeDelta& other) const {return TimeDelta(0,0,0,0,0,0,getTotalNanoSeconds()-other.getTotalNanoSeconds());};
void TimeDelta::operator+=(const TimeDelta& other) {setNanoseconds(nanoseconds_ + other.getTotalNanoSeconds());};
void TimeDelta::operator-=(const TimeDelta& other) {setNanoseconds(nanoseconds_ - other.getTotalNanoSeconds());};
bool TimeDelta::operator==(const TimeDelta& other) const {return other.getTotalNanoSeconds()==getTotalNanoSeconds();};
bool TimeDelta::operator!=(const TimeDelta& other) const {return other.getTotalNanoSeconds()!=getTotalNanoSeconds();}; 
bool TimeDelta::operator<(const TimeDelta& other) const {return other.getTotalNanoSeconds()>getTotalNanoSeconds();};
bool TimeDelta::operator<=(const TimeDelta& other) const {return other.getTotalNanoSeconds()>=getTotalNanoSeconds();};
bool TimeDelta::operator>=(const TimeDelta& other) const {return other.getTotalNanoSeconds()<=getTotalNanoSeconds();};
bool TimeDelta::operator>(const TimeDelta& other) const {return other.getTotalNanoSeconds()<getTotalNanoSeconds();};

long long TimeDelta::getTotalSeconds() const
{
    long long interTotal = 60*(days_*24*60+hours_*60+minutes_)+seconds_;
    long long microSecondsInSeconds = round(microseconds_/static_cast<int>(EpochTimestampType::MICROSECONDS)); 
    long long milliSecondsInSeconds = round(milliseconds_/static_cast<int>(EpochTimestampType::MILLISECONDS)); 
    long long nanoSecondsInSeconds = round(nanoseconds_/static_cast<int>(EpochTimestampType::NANOSECONDS)); 
    return interTotal+microSecondsInSeconds+milliSecondsInSeconds+nanoSecondsInSeconds;
}

long long TimeDelta::getTotalMilliSeconds() const
{
    long long interTotal = 1000*(60*(days_*24*60+hours_*60+minutes_)+seconds_);
    long long microSecondsInMilliSeconds = round(microseconds_*static_cast<int>(EpochTimestampType::MILLISECONDS)/static_cast<int>(EpochTimestampType::MICROSECONDS)); 
    long long nanoSecondsInMilliSeconds = round(nanoseconds_*static_cast<int>(EpochTimestampType::MILLISECONDS)/static_cast<int>(EpochTimestampType::NANOSECONDS)); 
    return interTotal + milliseconds_ + microSecondsInMilliSeconds + nanoSecondsInMilliSeconds;
}

long long TimeDelta::getTotalMicroSeconds() const
{
    long long interTotal = 1000*(60*(days_*24*60+hours_*60+minutes_)+seconds_) + milliseconds_;
    long long nanoSecondsInMicroSeconds = round(nanoseconds_*static_cast<int>(EpochTimestampType::MICROSECONDS)/static_cast<int>(EpochTimestampType::NANOSECONDS)); 
    return microseconds_ + 1000*interTotal + nanoSecondsInMicroSeconds;
}

long long TimeDelta::getTotalNanoSeconds() const
{
    long long interTotal = 1000*(60*(days_*24*60+hours_*60+minutes_)+seconds_) + milliseconds_;
    long long interTotal2 = 1000*interTotal + microseconds_; 
    return 1000*interTotal2+nanoseconds_;
}


