#include <iostream>
#include <cassert>
#include "../include/core-datetime/sequence.hpp"

DatetimeSequence getSequence() {

    std::set<int> timestampsVector = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824854400,
        1840665600, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982707200,
        1998432000, 2014243200, 2029968000, 2045779200, 2061504000,
        2077315200
    };

    DatetimeSequence sequence = DatetimeSequence();
    for (int t: timestampsVector){sequence.add(DateTime(t,EpochTimestampType::SECONDS));}
    return sequence;
}

void testBasics() {

    DatetimeSequence seq = getSequence(); 

    assert(seq.isExisting(DateTime(1761868800,EpochTimestampType::SECONDS)));
    assert(seq.isExisting(DateTime(1966896000,EpochTimestampType::SECONDS)));
    assert(!seq.isExisting(DateTime(1976896000,EpochTimestampType::SECONDS)));

    assert(seq.getLength()==21); 

    assert(seq.getIndex(DateTime(1761868800,EpochTimestampType::SECONDS)) == 0);
    assert(seq.getIndex(DateTime(1966896000,EpochTimestampType::SECONDS)) == 13);
    assert(seq.getIndex(DateTime(1976896000,EpochTimestampType::SECONDS)) == -1);

    assert(seq.getStart().value() == DateTime(1761868800,EpochTimestampType::SECONDS));
    assert(seq.getEnd().value() == DateTime(2077315200,EpochTimestampType::SECONDS));

    assert(!DatetimeSequence().getStart().has_value());
    assert(!DatetimeSequence().getEnd().has_value());

}

void testAddRemove() {

    DatetimeSequence sequence = getSequence(); 

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
}

void testNextPrevious() {

    DatetimeSequence sequence = getSequence(); 

    // 1) first datetime of the sequence 
    DateTime referenceDt = DateTime(1761868800, EpochTimestampType::SECONDS);
    assert(sequence.getNext(referenceDt).value() == DateTime(1777507200, EpochTimestampType::SECONDS));
    assert(!sequence.getPrevious(referenceDt).has_value());

    // 2) after last datetime of the sequence 
    referenceDt = DateTime(2077315200, EpochTimestampType::SECONDS) + TimeDelta(1,0,0,0,0,0,0);
    assert(!sequence.getNext(referenceDt).has_value());
    assert(sequence.getPrevious(referenceDt).value() == DateTime(2077315200, EpochTimestampType::SECONDS));

    // 3) before first datetime of the sequence 
    referenceDt = DateTime(1761868800, EpochTimestampType::SECONDS) - TimeDelta(1,0,0,0,0,0,0);
    assert(sequence.getNext(referenceDt).value() == DateTime(1761868800, EpochTimestampType::SECONDS));
    assert(!sequence.getPrevious(referenceDt).has_value());

    // 4) Non-existing datetime in-bewteen
    int intermTimestamp = 1958084800;
    referenceDt = DateTime(intermTimestamp, EpochTimestampType::SECONDS);
    assert(sequence.getNext(referenceDt).value() == DateTime(1966896000, EpochTimestampType::SECONDS));
    assert(sequence.getPrevious(referenceDt).value() == DateTime(1951084800, EpochTimestampType::SECONDS));

    // 5) Exact datetime in-bewteen
    referenceDt = DateTime(1951084800, EpochTimestampType::SECONDS);
    assert(sequence.getNext(referenceDt).value() == DateTime(1966896000, EpochTimestampType::SECONDS));
    assert(sequence.getPrevious(referenceDt).value() == DateTime(1935273600, EpochTimestampType::SECONDS));

    // 6) last datetime of the sequence 
    referenceDt = DateTime(2077315200, EpochTimestampType::SECONDS);
    assert(!sequence.getNext(referenceDt).has_value());
    assert(sequence.getPrevious(referenceDt).value() == DateTime(2061504000, EpochTimestampType::SECONDS));
}

void testSub() {

    DatetimeSequence sequence = getSequence(); 

    DatetimeSequence subSeq1 = sequence.getSub(1,3); 
    std::set<DateTime> subSeqTest1 = {
        DateTime(1777507200, EpochTimestampType::SECONDS), 
        DateTime(1793318400, EpochTimestampType::SECONDS), 
        DateTime(1809043200, EpochTimestampType::SECONDS)
    };
    assert(subSeq1.get() == subSeqTest1);

    DatetimeSequence subSeq2 = sequence.getSub(DateTime(1919548800, EpochTimestampType::SECONDS),DateTime(1982707200, EpochTimestampType::SECONDS)); 
    std::set<DateTime> subSeqTest2 = {
        DateTime(1919548800, EpochTimestampType::SECONDS), 
        DateTime(1935273600, EpochTimestampType::SECONDS), 
        DateTime(1951084800, EpochTimestampType::SECONDS), 
        DateTime(1966896000, EpochTimestampType::SECONDS), 
        DateTime(1982707200, EpochTimestampType::SECONDS)
    };
    assert(subSeq2.get() == subSeqTest2);

    DatetimeSequence subSeq3 = sequence.getSub(2,1); 
    assert(subSeq3.getLength() == 0);

    DatetimeSequence subSeq4 = sequence.getSub(DateTime(1982707200, EpochTimestampType::SECONDS),DateTime(1919548800, EpochTimestampType::SECONDS)); 
    assert(subSeq4.getLength() == 0);
}

int main() {

    testBasics();
    testAddRemove();
    testNextPrevious();
    testSub();
    std::cout << "All tests for the datetime sequence object have been passed successfully !" << std::endl;
    return 0; 
}

