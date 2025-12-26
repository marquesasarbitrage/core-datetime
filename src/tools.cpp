#include <iostream>
#include "../include/core-datetime/tools.hpp"

namespace DateTimeTools {

    bool isWeekEnd(const DateTime& date) {return date.getCTimeObject().tm_wday == 0 ? true : date.getCTimeObject().tm_wday == 6 ? true : false;}

    bool isEndMonth(const DateTime& date)
    {
        std::tm t = date.getCTimeObject();
        int year = getYear(date); 
        int lastDay = daysInMonth[t.tm_mon];
        if (t.tm_mon == 1 and isLeapYear(year)) lastDay = 29;
        return t.tm_mday == lastDay;
    }

    int getYear(const DateTime& date) {return date.getCTimeObject().tm_year + 1900;}

    bool isLeapYear(const DateTime& date){return isLeapYear(date.getCTimeObject().tm_year + 1900);}

    bool isLeapYear(int year){return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));}
    
    TimeDelta getTimeInLeapYear(const DateTime& startDate, const DateTime& endDate)
    {
        int endYear = getYear(endDate);
        int startYear = getYear(startDate);
        int yearDiff = endYear - startYear;
        TimeDelta output = TimeDelta(0,0,0,0,0,0,0);
        if (yearDiff == 0 && isLeapYear(endDate)) output += endDate-startDate;
        else 
        {
            for (int i = 1; i<=yearDiff; i++)
            {
                startYear += 1; 
                if (isLeapYear(startYear)) 
                {
                    if (i == yearDiff) output += endDate - getYearBeginningDate(endDate);
                    else output += TimeDelta(366,0,0,0,0,0,0); 
                    
                } else output += TimeDelta(0,0,0,0,0,0,0);
            }
        }
        return output;
    }
    
    DateTime getMidnightDateTime(const DateTime& date)
    {
        std::time_t timestamp = date.getConvertedTimestampType(EpochTimestampType::SECONDS).getTimestamp();
        std::tm* local_tm = std::gmtime(&timestamp);
        local_tm->tm_hour = 0;
        local_tm->tm_min  = 0;
        local_tm->tm_sec  = 0;
        return DateTime(static_cast<long long>(timegm(local_tm)), EpochTimestampType::SECONDS);
    }

    DateTime getYearBeginningDate(const DateTime& date)
    {
        std::time_t timestamp = date.getConvertedTimestampType(EpochTimestampType::SECONDS).getTimestamp();
        std::tm* local_tm = std::gmtime(&timestamp);
        local_tm->tm_hour = 0;
        local_tm->tm_min  = 0;
        local_tm->tm_sec  = 0;
        local_tm->tm_mday = 1; 
        local_tm->tm_mon = 0; 
        long long timestampAsLong = static_cast<long long>(timegm(local_tm)); 
        return DateTime(timestampAsLong, EpochTimestampType::SECONDS);
    }

    Sequence::Sequence() = default;
    Sequence::Sequence(const std::set<DateTime>& sequence): sequence_(sequence){};

    int Sequence::getLength() const {return sequence_.size();}
    bool Sequence::isExisting(const DateTime& referenceTime) const {return sequence_.find(referenceTime) != sequence_.end();}
    std::shared_ptr<DateTime> Sequence::getStart() const {if (sequence_.empty()) return nullptr; return std::make_shared<DateTime>(*sequence_.begin());}
    std::shared_ptr<DateTime> Sequence::getEnd() const {if (sequence_.empty()) return nullptr; return std::make_shared<DateTime>(*sequence_.rbegin());}

    void Sequence::add(const DateTime& date) {sequence_.insert(date);}
    void Sequence::remove(const DateTime& date) {sequence_.erase(date);}

    std::shared_ptr<DateTime> Sequence::getNext(const DateTime& referenceTime) const 
    {
        if (sequence_.empty()) return nullptr;
        auto it = sequence_.upper_bound(referenceTime);
        if (it == sequence_.end()) return nullptr;
        return std::make_shared<DateTime>(*it);
    }

    std::shared_ptr<DateTime> Sequence::getLast(const DateTime& referenceTime) const 
    {
        if (sequence_.empty())return nullptr;
        auto it = sequence_.lower_bound(referenceTime);
        if (it == sequence_.begin()) return nullptr;
        if (it == sequence_.end() || *it != referenceTime)
            --it;
        if (*it == referenceTime) --it;
        return std::make_shared<DateTime>(*it);
    }

    int Sequence::getIndex(const DateTime& referenceTime) const {
        auto it = sequence_.find(referenceTime);
        if (it == sequence_.end()) return -1;
        return static_cast<int>(std::distance(sequence_.begin(), it));
    }

    Sequence Sequence::getSubSequence(int startIndex, int endIndex)
    {
        int n = getLength();
        startIndex = std::max(0,std::min(startIndex, n)), endIndex = std::max(0,std::min(endIndex, n)); 
        Sequence subSequence;
        if (sequence_.empty() or startIndex>=endIndex) ; 
        else {    
            int idx = 0;
            for (const auto& dt : sequence_) {
                if (idx >= startIndex && idx <= endIndex) subSequence.add(dt);
                if (idx == endIndex) break;
                idx++;
            }
        }
        return subSequence;
    }

    Sequence Sequence::getSubSequence(const DateTime& startDate, const DateTime& endDate)
    {
        return getSubSequence(getIndex(startDate), getIndex(endDate));
    }

    std::set<DateTime> Sequence::getDataset() const {return sequence_;}

    DateTime getFromString(std::string dateString, std::string format) {

        std::tm tm{};
        int y, m, d;

        sscanf(dateString.c_str(), "%d-%d-%d", &y, &m, &d);

        if (format == "YYYY-MM-DD") {sscanf(dateString.c_str(), "%d-%d-%d", &y, &m, &d);} 

        else if (format == "YYYY-DD-MM") {sscanf(dateString.c_str(), "%d-%d-%d", &y, &d, &m);} 
        
        else throw InvalidDateFormatError(format);


        if (y < 1900) throw InvalidDateValueError(dateString); 

        else { 
            if (m < 1 || m > 12) throw InvalidDateValueError(dateString); 
            else {
                int maxDays = daysInMonth[m-1];
                if (m != 2) {

                    if (d < 1 || d > maxDays) throw InvalidDateValueError(dateString); 

                }
                else {
                    if (isLeapYear(y)) {
                        if (d < 1 || d > 29) throw InvalidDateValueError(dateString); 
                    } else {
                        if (d < 1 || d > 28) throw InvalidDateValueError(dateString) ;
                    }
                }
            }
        }

        tm.tm_year = y - 1900; // years since 1900
        tm.tm_mon  = m - 1;    // months since January [0,11]
        tm.tm_mday = d;
        tm.tm_hour = 0;
        tm.tm_min  = 0;
        tm.tm_sec  = 0;
        tm.tm_isdst = 0;

    #if defined(_WIN32)
        // Windows has _mkgmtime
        std::time_t t = _mkgmtime(&tm);
    #else
        // POSIX
        std::time_t t = timegm(&tm);
    #endif

        return DateTime(static_cast<long long>(t), EpochTimestampType::SECONDS);
    }

    std::vector<DateTime> getSpecificWeekDayInMonth(int month, int year, int weekDay) {

        std::vector<DateTime> output;
        try {
            if (weekDay<0 or weekDay>6) return output;
            std::string firstDayString = std::to_string(year) + "-" +  std::to_string(month) + "-1";
            DateTime firstDay = getFromString(firstDayString, "YYYY-MM-DD");
             int monthBeginWeekDay = firstDay.getCTimeObject().tm_wday;
            int next;
            if (monthBeginWeekDay<=weekDay) next = weekDay-monthBeginWeekDay; 
            else next = 7-monthBeginWeekDay+weekDay;

            
            output.push_back(firstDay + TimeDelta(next,0,0,0,0,0,0)); 
            output.push_back(firstDay + TimeDelta(next+7,0,0,0,0,0,0)); 
            output.push_back(firstDay + TimeDelta(next+14,0,0,0,0,0,0)); 
            output.push_back(firstDay + TimeDelta(next+21,0,0,0,0,0,0)); 

            DateTime lastDate = firstDay + TimeDelta(next+28,0,0,0,0,0,0);
            if (lastDate.getCTimeObject().tm_mon+1==month) output.push_back(lastDate); 

            return output;

        } catch (const std::exception& e) {

            return output;
        }
    }

};