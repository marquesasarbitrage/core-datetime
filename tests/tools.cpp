#include <iostream>
#include <cassert>
#include "../include/core-datetime/tools.hpp"

void testFunctions()
{
    // Friday 31 October 2025 00:00:00
    DateTime date1 = DateTime(1761868800, EpochTimestampType::SECONDS); 

    assert(DateTimeTools::isWeekEnd(date1)==false); 
    assert(DateTimeTools::isWeekEnd(date1+TimeDelta(1,0,0,0,0,0,0))==true); 

    assert(DateTimeTools::isEndMonth(date1)==true); 
    assert(DateTimeTools::isEndMonth(date1-TimeDelta(1,0,0,0,0,0,0))==false);

    assert(DateTimeTools::getYear(date1)==2025);

    assert(DateTimeTools::isLeapYear(2025)==false);
    assert(DateTimeTools::isLeapYear(2028)==true);
    assert(DateTimeTools::isLeapYear(date1)==false);
    assert(DateTimeTools::isLeapYear(date1+TimeDelta(365*3,0,0,0,0,0,0))==true);

    assert(DateTimeTools::getMidnightDateTime(date1 + TimeDelta(0,8,0,0,0,0,0))==date1); 
    assert(DateTimeTools::getYearBeginningDate(date1)==DateTime(1735689600,EpochTimestampType::SECONDS)); 

    // 25 Août 2025 21:00:00 
    DateTime referenceTime = DateTime(1756155600,EpochTimestampType::SECONDS); 
    // 14 Novembre 2026 21:00:00 
    DateTime d2 = DateTime(1794690000,EpochTimestampType::SECONDS); 
    // 18 Mai 2027 21:00:00 
    DateTime d3 = DateTime(1810674000,EpochTimestampType::SECONDS); 
    // 31 Octobre 2028 21:00:00 
    DateTime d4 = DateTime(1856638800,EpochTimestampType::SECONDS); 
    // 30 Septemmbre 2029 21:00:00 
    DateTime d5 = DateTime(1885496400,EpochTimestampType::SECONDS);

    assert(DateTimeTools::getTimeInLeapYear(referenceTime,d2) == TimeDelta(0,0,0,0,0,0,0)); 
    assert(DateTimeTools::getTimeInLeapYear(referenceTime,d3) == TimeDelta(0,0,0,0,0,0,0)); 
    assert(DateTimeTools::getTimeInLeapYear(referenceTime,d5) == TimeDelta(366,0,0,0,0,0,0)); 
    assert(DateTimeTools::getTimeInLeapYear(referenceTime,d4) == TimeDelta(304,21,0,0,0,0,0)); 
    
    std::cout << "All datetime tool function tests has passed." << std::endl; 
}

void testSequenceObject()
{
    std::set<int> timestampsVector = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824854400,
        1840665600, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982707200,
        1998432000, 2014243200, 2029968000, 2045779200, 2061504000,
        2077315200
    };

    DateTimeTools::Sequence sequence = DateTimeTools::Sequence();
    for (int t: timestampsVector){sequence.add(DateTime(t,EpochTimestampType::SECONDS));}

    assert(sequence.getLength()==21); 
    assert(sequence.isExisting(DateTime(1761868800,EpochTimestampType::SECONDS))==true); 
    assert(sequence.isExisting(DateTime(1761868800,EpochTimestampType::SECONDS)+TimeDelta(1,0,0,0,0,0,0))==false); 

    assert(*sequence.getStart()==DateTime(1761868800,EpochTimestampType::SECONDS)); 
    assert(*sequence.getEnd()==DateTime(2077315200,EpochTimestampType::SECONDS)); 

    assert(DateTimeTools::Sequence().getStart()==nullptr); 
    assert(DateTimeTools::Sequence().getStart()==nullptr); 

    int i = 0; 
    for (int t: timestampsVector) {assert(sequence.getIndex(DateTime(t,EpochTimestampType::SECONDS))==i); i++;}

    DateTime newDt = DateTime(1761868800, EpochTimestampType::SECONDS)-TimeDelta(1,0,0,0,0,0,0);
    sequence.add(newDt);
    assert(sequence.isExisting(newDt)==true); 
    assert(*sequence.getStart()==newDt); 
    sequence.remove(newDt);
    assert(sequence.isExisting(newDt)==false); 
    assert(*sequence.getStart()==DateTime(1761868800,EpochTimestampType::SECONDS)); 

    newDt = DateTime(2077315200, EpochTimestampType::SECONDS)+TimeDelta(1,0,0,0,0,0,0);
    sequence.add(newDt);
    assert(sequence.isExisting(newDt)==true); 
    assert(*sequence.getEnd()==newDt); 
    sequence.remove(newDt);
    assert(sequence.isExisting(newDt)==false); 
    assert(*sequence.getEnd()==DateTime(2077315200,EpochTimestampType::SECONDS)); 

    newDt = DateTime(1761868800, EpochTimestampType::SECONDS)+TimeDelta(1,0,0,0,0,0,0);
    sequence.add(newDt);
    assert(sequence.isExisting(newDt)==true); 
    assert(sequence.getIndex(newDt)==1); 
    sequence.remove(newDt);
    assert(sequence.isExisting(newDt)==false); 
    assert(sequence.getIndex(DateTime(1777507200,EpochTimestampType::SECONDS))==1); 

    newDt = DateTime(2077315200, EpochTimestampType::SECONDS)-TimeDelta(1,0,0,0,0,0,0);
    sequence.add(newDt);
    assert(sequence.isExisting(newDt)==true); 
    assert(sequence.getIndex(newDt)==20); 
    sequence.remove(newDt);
    assert(sequence.isExisting(newDt)==false); 
    assert(sequence.getIndex(DateTime(2061504000,EpochTimestampType::SECONDS))==19); 

    // 1) first datetime of the sequence 
    DateTime referenceDt = DateTime(1761868800, EpochTimestampType::SECONDS);
    assert(*sequence.getNext(referenceDt) == DateTime(1777507200, EpochTimestampType::SECONDS));
    assert(sequence.getLast(referenceDt) == nullptr);

    // 2) after last datetime of the sequence 
    referenceDt = DateTime(2077315200, EpochTimestampType::SECONDS) + TimeDelta(1,0,0,0,0,0,0);
    assert(sequence.getNext(referenceDt) == nullptr);
    assert(*sequence.getLast(referenceDt) == DateTime(2077315200, EpochTimestampType::SECONDS));

    // 3) before first datetime of the sequence 
    referenceDt = DateTime(1761868800, EpochTimestampType::SECONDS) - TimeDelta(1,0,0,0,0,0,0);
    assert(*sequence.getNext(referenceDt) == DateTime(1761868800, EpochTimestampType::SECONDS));
    assert(sequence.getLast(referenceDt) == nullptr);

    // 4) Non-existing datetime in-bewteen
    int intermTimestamp = 1958084800;
    referenceDt = DateTime(intermTimestamp, EpochTimestampType::SECONDS);
    assert(*sequence.getNext(referenceDt) == DateTime(1966896000, EpochTimestampType::SECONDS));
    assert(*sequence.getLast(referenceDt) == DateTime(1951084800, EpochTimestampType::SECONDS));

    // 5) Exact datetime in-bewteen
    referenceDt = DateTime(1951084800, EpochTimestampType::SECONDS);
    assert(*sequence.getNext(referenceDt) == DateTime(1966896000, EpochTimestampType::SECONDS));
    assert(*sequence.getLast(referenceDt) == DateTime(1935273600, EpochTimestampType::SECONDS));

    // 6) last datetime of the sequence 
    referenceDt = DateTime(2077315200, EpochTimestampType::SECONDS);
    assert(sequence.getNext(referenceDt) == nullptr);
    assert(*sequence.getLast(referenceDt) == DateTime(2061504000, EpochTimestampType::SECONDS));

    DateTimeTools::Sequence subSeq1 = sequence.getSubSequence(1,3); 
    std::set<DateTime> subSeqTest1 = {
        DateTime(1777507200, EpochTimestampType::SECONDS), 
        DateTime(1793318400, EpochTimestampType::SECONDS), 
        DateTime(1809043200, EpochTimestampType::SECONDS)
    };
    assert(subSeq1.getDataset() == subSeqTest1);

    DateTimeTools::Sequence subSeq2 = sequence.getSubSequence(DateTime(1919548800, EpochTimestampType::SECONDS),DateTime(1982707200, EpochTimestampType::SECONDS)); 
    std::set<DateTime> subSeqTest2 = {
        DateTime(1919548800, EpochTimestampType::SECONDS), 
        DateTime(1935273600, EpochTimestampType::SECONDS), 
        DateTime(1951084800, EpochTimestampType::SECONDS), 
        DateTime(1966896000, EpochTimestampType::SECONDS), 
        DateTime(1982707200, EpochTimestampType::SECONDS)
    };
    assert(subSeq2.getDataset() == subSeqTest2);

    DateTimeTools::Sequence subSeq3 = sequence.getSubSequence(2,1); 
    assert(subSeq3.getLength() == 0);

    DateTimeTools::Sequence subSeq4 = sequence.getSubSequence(DateTime(1982707200, EpochTimestampType::SECONDS),DateTime(1919548800, EpochTimestampType::SECONDS)); 
    assert(subSeq4.getLength() == 0);

    std::cout << "All Sequence object tests has been passed." << std::endl; 
}

int main()
{
    testFunctions();
    testSequenceObject();
    return 0; 
}