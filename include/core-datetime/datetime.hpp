#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "errors.hpp"

enum class EpochTimestampType {SECONDS = 1, MILLISECONDS = 1000, MICROSECONDS = 1000000, NANOSECONDS = 1000000000 };

class TimeDelta
{
    public:
        TimeDelta(long long days, long long hours, long long minutes, long long seconds, 
            long long milliseconds, long long microseconds, long long nanoseconds);
        TimeDelta();
        ~TimeDelta(){};

        long long getTotalSeconds() const;
        long long getTotalMilliSeconds() const;
        long long getTotalMicroSeconds() const;
        long long getTotalNanoSeconds() const;
        void setDays(long long n);
        void setHours(long long n);
        void setMinutes(long long n);
        void setSeconds(long long n);
        void setMicroseconds(long long n);
        void setMilliseconds(long long n);
        void setNanoseconds(long long n); 
        TimeDelta operator+(const TimeDelta& other) const;
        TimeDelta operator-(const TimeDelta& other) const;
        void operator+=(const TimeDelta& other);
        void operator-=(const TimeDelta& other);
        bool operator==(const TimeDelta& other) const;
        bool operator!=(const TimeDelta& other) const; 
        bool operator<(const TimeDelta& other) const;
        bool operator<=(const TimeDelta& other) const;
        bool operator>=(const TimeDelta& other) const;
        bool operator>(const TimeDelta& other) const;

    private:
        long long days_; 
        long long hours_; 
        long long minutes_; 
        long long seconds_; 
        long long milliseconds_; 
        long long microseconds_;
        long long nanoseconds_;
}; 

class DateTime
{
    public:

        DateTime(long long timestamp, EpochTimestampType type);
        DateTime();
        ~DateTime(){};

        long long getTimestamp() const;
        EpochTimestampType getTimestampType() const;
        std::tm getCTimeObject() const;
        std::string asString();
        DateTime getConvertedTimestampType(const EpochTimestampType type) const;
        void convertTimestampType(const EpochTimestampType type);
        void setStringFormat(std::string format); 

        DateTime operator+(const TimeDelta& other) const; 
        DateTime operator-(const TimeDelta& other) const; 
        TimeDelta operator-(const DateTime& other) const; 
        void operator+=(const TimeDelta& other); 
        void operator-=(const TimeDelta& other); 
        bool operator==(const DateTime& other) const; 
        bool operator!=(const DateTime& other) const; 
        bool operator<(const DateTime& other) const; 
        bool operator<=(const DateTime& other) const; 
        bool operator>=(const DateTime& other) const; 
        bool operator>(const DateTime& other) const; 

    private:
        void setTimestamp(const long long timestamp);
        void setTimestampType(const EpochTimestampType type);
        long long tmsp_; 
        EpochTimestampType type_; 
        std::string str_format_; 
};



