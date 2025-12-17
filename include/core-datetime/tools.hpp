#pragma once 
#include <iostream>
#include <set>
#include "datetime.hpp"

namespace DateTimeTools {

    static constexpr double dayInNanoSeconds = static_cast<double>(EpochTimestampType::NANOSECONDS)*24.0*60.0*60.0;
    static constexpr int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int getYear(const DateTime& date); 
    bool isWeekEnd(const DateTime& date);
    bool isEndMonth(const DateTime& date);
    bool isLeapYear(int year);
    bool isLeapYear(const DateTime& date);
    TimeDelta getTimeInLeapYear(const DateTime& startDate, const DateTime& endDate);
    DateTime getMidnightDateTime(const DateTime& date);
    DateTime getYearBeginningDate(const DateTime& date);
    DateTime getFromString(std::string dateString, std::string format);

    class Sequence 
    {
        public: 
            Sequence(); 
            Sequence(const std::set<DateTime>& sequence); 
            ~Sequence() = default;

            std::set<DateTime> getDataset() const;
            int getLength() const;
            bool isExisting(const DateTime& referenceTime) const;
            std::shared_ptr<DateTime> getLast(const DateTime& referenceTime) const; 
            std::shared_ptr<DateTime> getNext(const DateTime& referenceTime) const; 
            std::shared_ptr<DateTime> getStart() const; 
            std::shared_ptr<DateTime> getEnd() const; 
            int getIndex(const DateTime& referenceTime) const;
            Sequence getSubSequence(const DateTime& startDate, const DateTime& endDate); 
            Sequence getSubSequence(int startIndex, int endIndex); 

            void add(const DateTime& date); 
            void remove(const DateTime& date);
        
        private:
            std::set<DateTime> sequence_;

    };


};

