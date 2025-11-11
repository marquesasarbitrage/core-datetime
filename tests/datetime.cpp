#include <iostream>
#include <cassert>
#include "../include/core-datetime/datetime.hpp"
#include "../include/core-datetime/errors.hpp"

void testTimeDelta() {
    // Test constructor and getters
    TimeDelta delta(1, 2, 3, 4, 500, 600, 700); // 1 day, 2 hours, 3 minutes, 4 seconds, 500 ms, 600 µs, 700 ns

    // Test get_total_seconds
    long long totalSeconds = delta.getTotalSeconds();
    assert(totalSeconds == 93784); // 1 day = 86400 seconds, 2 hours = 7200 seconds, 3 minutes = 180 seconds, 4 seconds = 4

    // Test get_total_milliseconds
    long long totalMilliSeconds = delta.getTotalMilliSeconds();
    assert(totalMilliSeconds == 93784500); // Total seconds * 1000 + 500 ms

    // Test get_total_microseconds
    long long totalMicroSeconds = delta.getTotalMicroSeconds();
    assert(totalMicroSeconds == 93784500600); // Total milliseconds * 1000 + 600 µs

    // Test get_total_nanoseconds
    long long totalNanoSeconds = delta.getTotalNanoSeconds();
    assert(totalNanoSeconds == 93784500600700); // Total microseconds * 1000 + 700 ns

    // Test setters
    delta.setDays(0);
    delta.setHours(0);
    delta.setMinutes(0);
    delta.setSeconds(10);
    delta.setMilliseconds(0);
    delta.setMicroseconds(0);
    delta.setNanoseconds(0);

    // Verify updated values
    assert(delta.getTotalSeconds() == 10);
    assert(delta.getTotalMilliSeconds() == 10000);
    assert(delta.getTotalMicroSeconds() == 10000000);
    assert(delta.getTotalNanoSeconds() == 10000000000);

    std::cout << "All tests passed for TimeDelta!" << std::endl;
}

void testDateTimeConstructor() {
    // Test valid constructor
    DateTime dt(1625097600, EpochTimestampType::SECONDS); // Example timestamp
    assert(dt.getTimestamp() == 1625097600);
    assert(dt.getTimestampType() == EpochTimestampType::SECONDS);

    // Test invalid constructor (negative timestamp)
    try {
        DateTime dtInvalid(-1, EpochTimestampType::SECONDS);
        assert(false); // Should not reach here
    } catch (const NegativeEpochTimestampError& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
}

void testGetCTimeObject() {
    DateTime dt(1625097600, EpochTimestampType::SECONDS); // Example timestamp
    auto time_info = dt.getCTimeObject();
    assert(time_info.tm_year + 1900 == 2021); // Year
    assert(time_info.tm_mon + 1 == 7);        // Month (July)
    assert(time_info.tm_mday == 1);           // Day
}

void testConvertTimestampType() {
    DateTime dt(1625097600, EpochTimestampType::SECONDS); // Example timestamp
    dt.convertTimestampType(EpochTimestampType::MILLISECONDS);
    assert(dt.getTimestamp() == 1625097600000); // Converted to milliseconds
    assert(dt.getTimestampType() == EpochTimestampType::MILLISECONDS);
}

void testGetConvertedTimestampType() {
    DateTime dt(1625097600, EpochTimestampType::SECONDS); // Example timestamp
    DateTime converted = dt.getConvertedTimestampType(EpochTimestampType::MILLISECONDS);
    assert(converted.getTimestamp() == 1625097600000); // Converted to milliseconds
    assert(converted.getTimestampType() == EpochTimestampType::MILLISECONDS);
}

void testDateTimeOperators() {
    DateTime dt1(1625097600, EpochTimestampType::SECONDS); // Example timestamp
    TimeDelta delta(0, 1, 0, 0, 0, 0, 0); // 1 hour

    dt1 += delta; 
    assert(dt1.getTimestamp() == 1625101200);
    dt1 -= delta; 
    assert(dt1.getTimestamp() == 1625097600);

    // Test addition with TimeDelta
    DateTime dt2 = dt1 + delta;
    assert(dt2.getTimestamp() == 1625101200); // 1 hour later

    // Test subtraction with TimeDelta
    DateTime dt3 = dt1 - delta;
    assert(dt3.getTimestamp() == 1625094000); // 1 hour earlier

    // Test subtraction between DateTime objects
    TimeDelta diff = dt2 - dt1;
    assert(diff.getTotalSeconds() == 3600); // 1 hour difference

    // Test comparison operators
    assert(dt1 == dt1);
    assert(dt1 != dt2);
    assert(dt1 < dt2);
    assert(dt2 > dt1);
    assert(dt1 <= dt2);
    assert(dt2 >= dt1);
}

void testDateTime()
{
    testDateTimeConstructor(); 
    testGetCTimeObject();
    testConvertTimestampType(); 
    testGetConvertedTimestampType();
    testDateTimeOperators(); 
    std::cout << "All tests passed for DateTime!" << std::endl;
}

int main()
{
    testTimeDelta();
    testDateTime(); 
    return 0;
}