#include <iostream>
#include "../include/core-datetime/timedelta.hpp"

TimeDelta::TimeDelta(long long days, long long hours, long long minutes, long long seconds, 
long long milliseconds, long long microseconds, long long nanoseconds) {
    
    days_ = days; 
    hours_ = hours; 
    minutes_ = minutes; 
    seconds_ = seconds; 
    milliseconds_ = milliseconds; 
    microseconds_ = microseconds;
    nanoseconds_ = nanoseconds;
}

TimeDelta::Years::Years(int years): years_(years) {}

TimeDelta::Months::Months(int months): months_(months) {}

TimeDelta::TimeDelta():
days_(0)
, hours_(0)
, minutes_(0)
, seconds_(0)
, milliseconds_(0)
, microseconds_(0)
, nanoseconds_(0)
{};

void TimeDelta::setDays(long long n) { days_ = n; }

void TimeDelta::setHours(long long n) { hours_ = n; }

void TimeDelta::setMinutes(long long n) { minutes_ = n; }

void TimeDelta::setSeconds(long long n) { seconds_ = n; }

void TimeDelta::setMicroseconds(long long n) { microseconds_ = n; }

void TimeDelta::setMilliseconds(long long n) { milliseconds_ = n; }

void TimeDelta::setNanoseconds(long long n) { nanoseconds_ = n; }

TimeDelta TimeDelta::operator+(const TimeDelta& other) const { return TimeDelta(0,0,0,0,0,0,getTotalNanoSeconds()+other.getTotalNanoSeconds()); }

TimeDelta TimeDelta::operator-(const TimeDelta& other) const { return TimeDelta(0,0,0,0,0,0,getTotalNanoSeconds()-other.getTotalNanoSeconds()); }

void TimeDelta::operator+=(const TimeDelta& other) { setNanoseconds(nanoseconds_ + other.getTotalNanoSeconds()); } 

void TimeDelta::operator-=(const TimeDelta& other) { setNanoseconds(nanoseconds_ - other.getTotalNanoSeconds()); }

bool TimeDelta::operator==(const TimeDelta& other) const { return other.getTotalNanoSeconds()==getTotalNanoSeconds(); }

bool TimeDelta::operator!=(const TimeDelta& other) const { return other.getTotalNanoSeconds()!=getTotalNanoSeconds(); }

bool TimeDelta::operator<(const TimeDelta& other) const { return other.getTotalNanoSeconds()>getTotalNanoSeconds(); }

bool TimeDelta::operator<=(const TimeDelta& other) const { return other.getTotalNanoSeconds()>=getTotalNanoSeconds(); }

bool TimeDelta::operator>=(const TimeDelta& other) const { return other.getTotalNanoSeconds()<=getTotalNanoSeconds(); }

bool TimeDelta::operator>(const TimeDelta& other) const { return other.getTotalNanoSeconds()<getTotalNanoSeconds(); }

long long TimeDelta::getTotalSeconds() const {

    long long totalSeconds =
        days_ * 86'400LL +
        hours_ * 3'600LL +
        minutes_ * 60LL +
        seconds_;

    totalSeconds += microseconds_ / 1'000LL;
    totalSeconds += milliseconds_ / 1'000'000LL;
    totalSeconds += nanoseconds_  / 1'000'000'000LL;

    return totalSeconds;
}

long long TimeDelta::getTotalMilliSeconds() const {

    long long totalMs =
        days_ * 86'400'000LL +
        hours_ * 3'600'000LL +
        minutes_ * 60'000LL +
        seconds_ * 1'000LL +
        milliseconds_;

    totalMs += microseconds_ / 1'000LL;
    totalMs += nanoseconds_  / 1'000'000LL;

    return totalMs;
}

long long TimeDelta::getTotalMicroSeconds() const {

    long long totalUs =
        days_ * 86'400'000'000LL +
        hours_ * 3'600'000'000LL +
        minutes_ * 60'000'000LL +
        seconds_ * 1'000'000LL +
        milliseconds_ * 1'000LL +
        microseconds_;

    totalUs += nanoseconds_ / 1'000LL;

    return totalUs;
}

long long TimeDelta::getTotalNanoSeconds() const {

    return
        days_ * 86'400'000'000'000LL +
        hours_ * 3'600'000'000'000LL +
        minutes_ * 60'000'000'000LL +
        seconds_ * 1'000'000'000LL +
        milliseconds_ * 1'000'000LL +
        microseconds_ * 1'000LL +
        nanoseconds_;
}


