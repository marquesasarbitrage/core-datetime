#include "../include/core-datetime/sequence.hpp"

DatetimeSequence::DatetimeSequence() = default; 

DatetimeSequence::DatetimeSequence(const std::set<DateTime>& sequence): sequence_(sequence) {}

void DatetimeSequence::add(const DateTime& date) { sequence_.insert(date); }

void DatetimeSequence::remove(const DateTime& date) { sequence_.erase(date); }

int DatetimeSequence::getLength() const { return sequence_.size(); }

std::set<DateTime> DatetimeSequence::get() const { return sequence_; }

std::vector<DateTime> DatetimeSequence::getAsVector() const { return std::vector<DateTime>(sequence_.begin(), sequence_.end());}

std::optional<DateTime> DatetimeSequence::getPrevious(const DateTime& date) const {

    auto it = sequence_.lower_bound(date);
    if (it == sequence_.begin()) return std::nullopt;
    --it;
    return *it;
}

std::optional<DateTime> DatetimeSequence::getNext(const DateTime& date) const {

    auto it = sequence_.upper_bound(date);
    if (it == sequence_.end()) return std::nullopt;
    return *it; 
}

std::optional<DateTime> DatetimeSequence::getStart() const {

    if (sequence_.empty()) return std::nullopt;
    return *sequence_.begin();
}

std::optional<DateTime> DatetimeSequence::getEnd() const {

    if (sequence_.empty()) return std::nullopt;
    return *sequence_.rbegin();
}

DatetimeSequence DatetimeSequence::getSub(int startIndex, int endIndex) const {

    // Algo optimized by ChatGPT
    DatetimeSequence result;
    int n = getLength();

    startIndex = std::clamp(startIndex, 0, n);
    endIndex   = std::clamp(endIndex,   0, n);

    if (startIndex >= endIndex) return result;

    int idx = 0;
    for (auto it = sequence_.begin(); it != sequence_.end(); ++it, ++idx) {
        if (idx > endIndex) break;
        if (idx >= startIndex) result.add(*it);
    }

    return result;
}

int DatetimeSequence::getIndex(const DateTime& date) const {

    auto it = sequence_.find(date);
    if (it == sequence_.end()) return -1;
    return static_cast<int>(std::distance(sequence_.begin(), it));
}

DatetimeSequence DatetimeSequence::getSub(const DateTime& startDate, const DateTime& endDate) const {

    return getSub(getIndex(startDate), getIndex(endDate));
}

bool DatetimeSequence::isExisting(DateTime date) { return sequence_.find(date) != sequence_.end(); }
