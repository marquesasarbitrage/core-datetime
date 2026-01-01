#include <iostream>
#include <cassert>
#include "../include/core-datetime/datetime.hpp"

void testTimestampConstructor() {

    DateTime dt1 = DateTime(1766939320,EpochTimestampType::SECONDS); 
    DateTime dt2 = DateTime(1766939320,EpochTimestampType::SECONDS, TimeZone::UTCP1);
    
    assert(dt1.getTimestamp()==1766939320);
    assert(dt2.getTimestamp()==1766939320);
    assert(dt1.getYear()==2025);
    assert(dt2.getYear()==2025);
    assert(dt1.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt2.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt1.getTimeZone()==TimeZone::UTC);
    assert(dt2.getTimeZone()==TimeZone::UTCP1);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 17:28:40 UTC+1");
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestamp()==1766939320000);
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::MILLISECONDS); 
    assert(dt1.getTimestamp()==1766939320000);
    assert(dt1.getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::SECONDS); 
    dt2.setTimeZone(TimeZone::UTCM6);
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 10:28:40 UTC-6");
}

void testCivilConstructor() {

    DateTime dt1 = DateTime(2025,12,28,16,28,40); 
    DateTime dt2 = DateTime(2025,12,28,17,28,40, TimeZone::UTCP1); 

    assert(dt1.getTimestamp()==1766939320);
    assert(dt2.getTimestamp()==1766939320);
    assert(dt1.getYear()==2025);
    assert(dt2.getYear()==2025);
    assert(dt1.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt2.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt1.getTimeZone()==TimeZone::UTC);
    assert(dt2.getTimeZone()==TimeZone::UTCP1);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 17:28:40 UTC+1");
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestamp()==1766939320000);
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::MILLISECONDS); 
    assert(dt1.getTimestamp()==1766939320000);
    assert(dt1.getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::SECONDS); 
    dt2.setTimeZone(TimeZone::UTCM6);
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 10:28:40 UTC-6");


}

void testStringConstructor() {

    DateTime dt1 = DateTime("2025-12-28 16:28:40", "YYYY-MM-DD HH:MM:SS"); 
    DateTime dt2 = DateTime("2025-12-28 17:28:40", "YYYY-MM-DD HH:MM:SS", TimeZone::UTCP1); 

    assert(dt1.getTimestamp()==1766939320);
    assert(dt2.getTimestamp()==1766939320);
    assert(dt1.getYear()==2025);
    assert(dt2.getYear()==2025);
    assert(dt1.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt2.getTimestampType()==EpochTimestampType::SECONDS);
    assert(dt1.getTimeZone()==TimeZone::UTC);
    assert(dt2.getTimeZone()==TimeZone::UTCP1);

    assert(dt1.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 16:28:40 UTC+0");
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 17:28:40 UTC+1");

    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestamp()==1766939320000);
    assert(dt1.getModifiedTimestampType(EpochTimestampType::MILLISECONDS).getTimestampType()==EpochTimestampType::MILLISECONDS);
    dt1.setTimestampType(EpochTimestampType::MILLISECONDS); 
    assert(dt1.getTimestamp()==1766939320000);
    assert(dt1.getTimestampType()==EpochTimestampType::MILLISECONDS);

    dt1.setTimestampType(EpochTimestampType::SECONDS); 
    dt2.setTimeZone(TimeZone::UTCM6);
    assert(dt2.asString("YYYY-MM-DD HH:MM:SS")=="2025-12-28 10:28:40 UTC-6");

}

void testOperators() {
    DateTime dt1(1625097600, EpochTimestampType::SECONDS); 
    TimeDelta delta(0, 1, 0, 0, 0, 0, 0); 

    dt1 += delta; 
    assert(dt1.getTimestamp() == 1625101200);
    dt1 -= delta; 
    assert(dt1.getTimestamp() == 1625097600);

    DateTime dt2 = dt1 + delta;
    assert(dt2.getTimestamp() == 1625101200); 

    DateTime dt3 = dt1 - delta;
    assert(dt3.getTimestamp() == 1625094000); 

    TimeDelta diff = dt2 - dt1;
    assert(diff.getTotalSeconds() == 3600);

    TimeDelta::Years diffYears1(1); 
    TimeDelta::Years difffYears2(3); 
    
    TimeDelta::Months diffMonth1(1); 
    TimeDelta::Months diffMonth2(25); 

    DateTime initialDate = DateTime(1767118789,EpochTimestampType::SECONDS);

    initialDate += diffYears1; 
    assert(initialDate.getTimestamp() == 1798654789);
    initialDate -= diffYears1; 
    assert(initialDate.getTimestamp() == 1767118789);
    initialDate += diffMonth1; 
    assert(initialDate.getTimestamp() == 1769797189);
    initialDate -= diffMonth1; 
    assert(initialDate.getTimestamp() == 1767118789);
    
    initialDate += difffYears2; 
    assert(initialDate.getTimestamp() == 1861813189);
    initialDate -= difffYears2; 
    assert(initialDate.getTimestamp() == 1767118789);
    
    initialDate += diffMonth2; 
    assert(initialDate.getTimestamp() == 1832869189);
    initialDate -= diffMonth2; 
    assert(initialDate.getTimestamp() == 1767118789);


    assert(dt1 == dt1);
    assert(dt1 != dt2);
    assert(dt1 < dt2);
    assert(dt2 > dt1);
    assert(dt1 <= dt2);
    assert(dt2 >= dt1);
}


int main() {

    testTimestampConstructor(); 
    testCivilConstructor();
    testStringConstructor();
    testOperators();
    std::cout << "All datetime object tests have been passed !" << std::endl;
    return 0;
}