#pragma once
#include <iostream>

class TimeDelta
{
    public:
        TimeDelta(long long days, long long hours, long long minutes, long long seconds, 
            long long milliseconds, long long microseconds, long long nanoseconds);
        TimeDelta();
        ~TimeDelta(){};

        struct Years { int years_; Years(int years); ~Years() = default; };
        struct Months { int months_; Months(int months); ~Months() = default; };

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

