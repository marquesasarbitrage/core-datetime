#include <iostream>
#include "../include/core-datetime/errors.hpp"

NegativeEpochTimestampError::NegativeEpochTimestampError(): message_(getMessageAsString()){}

const char* NegativeEpochTimestampError::what() const noexcept { return message_.c_str(); }

std::string NegativeEpochTimestampError::getMessageAsString() const{return "The epoch timestamp cannot be negative.";}

InvalidDateFormatError::InvalidDateFormatError(std::string format): format_(format), message_(getMessageAsString()){}

const char* InvalidDateFormatError::what() const noexcept { return message_.c_str(); }

std::string InvalidDateFormatError::getMessageAsString() const{ return "The date format " + format_ + " is unknown."; }

InvalidDateValueError::InvalidDateValueError(std::string date): date_(date), message_(getMessageAsString()){}

const char* InvalidDateValueError::what() const noexcept { return message_.c_str(); }

std::string InvalidDateValueError::getMessageAsString() const{ return "The date " + date_ + " is invalid and return undefined behaviors."; }