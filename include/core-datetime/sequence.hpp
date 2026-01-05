#pragma once 
#include <iostream>
#include <set>
#include <optional>
#include "datetime.hpp"

class DatetimeSequence {

    public: 
        DatetimeSequence(); 
        DatetimeSequence(const std::set<DateTime>& sequence); 
        virtual ~DatetimeSequence() = default;

        std::set<DateTime> get() const; 
        std::vector<DateTime> getAsVector() const;
        DatetimeSequence getSub(int startIndex, int endIndex) const; 
        DatetimeSequence getSub(const DateTime& startDate, const DateTime& endDate) const; 

        std::optional<DateTime> getPrevious(const DateTime& date) const; 
        std::optional<DateTime> getNext(const DateTime& date) const; 
        std::optional<DateTime> getStart() const; 
        std::optional<DateTime> getEnd() const; 

        bool isExisting(DateTime date); 
        int getLength() const;
        int getIndex(const DateTime& date) const;

        void add(const DateTime& date); 
        void remove(const DateTime& date);

    private: 
        std::set<DateTime> sequence_;
};