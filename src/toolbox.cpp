#include "../include/core-datetime/toolbox.hpp"

namespace DatetimeToolbox {

    void checkCivilDate(int year, int month, int day) {

        if (month > 12 or month < 1)  throw DatetimeErrorRegistry::InvalidCivilDateError();
        int n = (isLeapYear(year) && month ==2) ? 29 : daysInMonth[month-1]; 
        if (day > n or day < 1)  throw DatetimeErrorRegistry::InvalidCivilDateError();
    }

    void checkCivilHour(int hour, int minute, int second) {

        if (hour < 0 or hour > 23)  throw DatetimeErrorRegistry::InvalidCivilHourError();
        if (minute < 0 or minute > 59)  throw DatetimeErrorRegistry::InvalidCivilHourError();
        if (second < 0 or second > 59)  throw DatetimeErrorRegistry::InvalidCivilHourError();
    }

    bool isLeapYear(int year){return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));}

    long long getDaysSinceEpoch(int year, int month, int day) {

        // Algorithm from ChatGPT
        checkCivilDate(year,month,day);
        year -= month <= 2;
        const int era = (year >= 0 ? year : year - 399) / 400;
        const unsigned yoe = static_cast<unsigned>(year - era * 400);
        const unsigned doy = (153 * (month + (month > 2 ? -3 : 9)) + 2) / 5 + day - 1;
        const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
        return era * 146097LL + static_cast<long long>(doe) - 719468;
    }

    long long getTimestampFromCivilDateHour(int year, int month, int day, int hour, int minute, int second) {

        checkCivilHour(hour,minute,second);
        long long days = getDaysSinceEpoch(year, month, day);
        return days * 86400LL
            + hour   * 3600LL
            + minute * 60LL
            + second;
    }

    long long getTimestampFromCivilDateHourString(std::string dateString, std::string dateFormat) {

        
        int y, m, d, h = 0, mi = 0, s=0; 

        if (dateFormat == "YYYY-MM-DD") {sscanf(dateString.c_str(), "%d-%d-%d", &y, &m, &d);} 
        else if (dateFormat == "YYYY-DD-MM") {sscanf(dateString.c_str(), "%d-%d-%d", &y, &d, &m);} 
        else if (dateFormat == "YYYY/DD/MM") {sscanf(dateString.c_str(), "%d/%d/%d", &y, &d, &m);} 
        else if (dateFormat == "YYYY/MM/DD") {sscanf(dateString.c_str(), "%d/%d/%d", &y, &m, &d);} 
        else if (dateFormat == "YYYY-DD-MM HH:MM:SS") {sscanf(dateString.c_str(), "%d-%d-%d %d:%d:%d", &y, &d, &m, &h, &mi, &s);} 
        else if (dateFormat == "YYYY-MM-DD HH:MM:SS") {sscanf(dateString.c_str(), "%d-%d-%d %d:%d:%d", &y, &m, &d, &h, &mi, &s);} 
        else if (dateFormat == "YYYY/DD/MM HH:MM:SS") {sscanf(dateString.c_str(), "%d-%d-%d %d:%d:%d", &y, &d, &m, &h, &mi, &s);} 
        else throw DatetimeErrorRegistry::InvalidDateStringFormatError();

        checkCivilDate(y, m, d); 
        checkCivilHour(h, mi, s);
        return getTimestampFromCivilDateHour(y,m,d,h,mi,s);
    }

    std::tuple<int, int, int, int, int, int> getCivilFromTimestamp(long long tmsp) {

        // Algorithm from ChatGPT
        long long days = tmsp / 86400;
        long long secs = tmsp % 86400;

        if (secs < 0) { 
            secs += 86400;
            --days;
        }

        unsigned hour   = secs / 3600;
        secs           %= 3600;
        unsigned minute = secs / 60;
        unsigned second = secs % 60;

        long long z = days + 719468; 
        long long era = (z >= 0 ? z : z - 146096) / 146097;
        unsigned doe = static_cast<unsigned>(z - era * 146097);      
        unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365; 
        int y = static_cast<int>(yoe) + era * 400;
        unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);            
        unsigned mp = (5*doy + 2) / 153;                       
        unsigned day = doy - (153*mp + 2)/5 + 1;               
        unsigned month = mp + (mp < 10 ? 3 : -9);                     
        int year = y + (month <= 2);

        checkCivilDate(year, month, day); 
        checkCivilHour(hour,minute,second);

        return std::make_tuple(year, month, day, hour, minute, second);
    }

    std::string getCivilDateHourStringFromCivilDateHour(int year, int month, int day, int hour, int minute, int second, std::string dateFormat) {

        std::string YYYY = std::to_string(year);
        std::string DD = (day < 10 ? "0" : "") + std::to_string(day);
        std::string MM = (month < 10 ? "0" : "") + std::to_string(month);
        std::string HH = (hour < 10 ? "0" : "") + std::to_string(hour);
        std::string MI = (minute < 10 ? "0" : "") + std::to_string(minute);
        std::string SS = (second < 10 ? "0" : "") + std::to_string(second);

        if (dateFormat == "YYYY-MM-DD") return YYYY + "-" + MM + "-" + DD;

        if (dateFormat == "YYYY-DD-MM") return YYYY + "-" + DD + "-" + MM;

        if (dateFormat == "YYYY/MM/DD") return YYYY + "/" + MM + "/" + DD;

        if (dateFormat == "YYYY/DD/MM") return YYYY + "/" + DD + "/" + MM;

        if (dateFormat == "YYYY-MM-DD HH:MM:SS") return YYYY + "-" + MM + "-" + DD + " " +
                HH + ":" + MI + ":" + SS;

        if (dateFormat == "YYYY-DD-MM HH:MM:SS") return YYYY + "-" + DD + "-" + MM + " " +
                HH + ":" + MI + ":" + SS;

        if (dateFormat == "YYYY/MM/DD HH:MM:SS") return YYYY + "/" + MM + "/" + DD + " " +
                HH + ":" + MI + ":" + SS;

        if (dateFormat == "YYYY/DD/MM HH:MM:SS") return YYYY + "/" + DD + "/" + MM + " " +
                HH + ":" + MI + ":" + SS;

        throw DatetimeErrorRegistry::InvalidDateStringFormatError();
    }

    std::string getCivilDateHourStringFromTimestamp(long long tmsp, std::string dateFormat) {

        auto [year,month,day,hour,minute,second] = getCivilFromTimestamp(tmsp); 
        return getCivilDateHourStringFromCivilDateHour(year,month,day,hour,minute,second, dateFormat);
    }

    int getWeekDayFromTimestamp(long long tmsp) {

        // Algorithm from ChatGPT
        // Offset Here ? 
        return (static_cast<int>((tmsp / 86400 + 4) % 7 + 7) % 7);
    }

    int getWeekDayFromCivilDate(int year, int month, int day) {

        return (static_cast<int>((getDaysSinceEpoch(year,month,day) + 4) % 7 + 7) % 7);
    }

    int getFirstWeekDayOfMonth(int year, int month, int weekDay) {

        return 1 + (weekDay - getWeekDayFromCivilDate(year,month,1) + 7) % 7; 
    }

    int getSecondWeekDayOfMonth(int year, int month, int weekDay) { return getFirstWeekDayOfMonth(year,month,weekDay) + 7; }

    int getThirdWeekDayOfMonth(int year, int month, int weekDay) { return getFirstWeekDayOfMonth(year,month,weekDay) + 14; }

    int getFourthWeekDayOfMonth(int year, int month, int weekDay) { return getFirstWeekDayOfMonth(year,month,weekDay) + 21; }

    int getLastWeekDayOfMonth(int year, int month, int weekDay) {

        int fourth = getFourthWeekDayOfMonth(year,month,weekDay); 
        int fifth = fourth + 7; 
        int n = (isLeapYear(year) && month ==2) ? 29 : daysInMonth[month-1];
        return (fifth > n) ? fourth : fifth;
    }

    long long nowNanoSeconds() {

        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    bool isEndMonth(int year, int month, int day) { return getDaysInMonth(year,month)==day; }

    int getDaysInMonth(int year, int month) {

        return (month == 2 and isLeapYear(year)) ? 29 : DatetimeToolbox::daysInMonth[month-1];
    }

    std::tuple<int, int, int> addYearsToCivilDate(int year, int month, int day, int n) {

        // Optimized Algorithm by ChatGPT
        year += n;

        if (month == 2 && day == 29 && !isLeapYear(year)) {
            day = 28;
        }

        checkCivilDate(year, month, day);
        return std::make_tuple(year, month, day);
    }

    std::tuple<int, int, int> addMonthsToCivilDate(int year, int month, int day, int n) {

        // Optimized Algorithm by ChatGPT
        int y = year;
        int m = month + n;

        y += (m - 1) / 12;
        m  = (m - 1) % 12 + 1;
        if (m <= 0) {
            m += 12;
            y -= 1;
        }

        int maxDay = getDaysInMonth(y, m);
        int d = std::min(day, maxDay);

        checkCivilDate(y, m, d);
        return {y, m, d};
    }
}