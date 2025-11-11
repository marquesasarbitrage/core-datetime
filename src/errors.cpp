#include <iostream>
#include "../include/core-datetime/errors.hpp"

NegativeEpochTimestampError::NegativeEpochTimestampError(): message_(getMessageAsString()){};
const char* NegativeEpochTimestampError::what() const noexcept {return message_.c_str();};
std::string NegativeEpochTimestampError::getMessageAsString() const{return "The epoch timestamp cannot be negative.";}

