#include <iostream>
#include <cassert>
#include "../include/core-datetime/timedelta.hpp"

int main() {
    TimeDelta delta(1, 2, 3, 4, 500, 600, 700); 

    long long totalSeconds = delta.getTotalSeconds();
    assert(totalSeconds == 93784); 

    long long totalMilliSeconds = delta.getTotalMilliSeconds();
    assert(totalMilliSeconds == 93784500); 

    long long totalMicroSeconds = delta.getTotalMicroSeconds();
    assert(totalMicroSeconds == 93784500600); 

    long long totalNanoSeconds = delta.getTotalNanoSeconds();
    assert(totalNanoSeconds == 93784500600700);

    delta.setDays(0);
    delta.setHours(0);
    delta.setMinutes(0);
    delta.setSeconds(10);
    delta.setMilliseconds(0);
    delta.setMicroseconds(0);
    delta.setNanoseconds(0);

    assert(delta.getTotalSeconds() == 10);
    assert(delta.getTotalMilliSeconds() == 10000);
    assert(delta.getTotalMicroSeconds() == 10000000);
    assert(delta.getTotalNanoSeconds() == 10000000000);

    std::cout << "All tests passed for TimeDelta!" << std::endl;
    return 0;
}
