#include "../include/core-datetime/errors.hpp"

const char* DateTimeLibraryError::what() const noexcept
{
    if (cachedMessage_.empty()) {
            cachedMessage_ = getErrorMessage();  
        }
    return cachedMessage_.c_str();
}

namespace DatetimeErrorRegistry
{
    std::string InvalidCivilDateError::getErrorMessage() const {return "The year, month or day given to construct a civil date is invalid.";}
    
    std::string InvalidCivilHourError::getErrorMessage() const {return "The hour, minute or second given to construct a civil hour is invalid.";}

    std::string InvalidDateStringFormatError::getErrorMessage() const {return "The date string format is invalid.";}

    std::string UnknownDayCountConventionError::getErrorMessage() const {return "No method is defined to compute the year faction based on given day count convention.";}

    std::string InvalidStartEndDate::getErrorMessage() const {return "Start date cannot be set after the end date.";}

    std::string UnknownBusinessDayConventionError::getErrorMessage() const {return "No method is defined to compute the business day adjustement for the convention given.";}

    std::string UnknownHolidayCalendarError::getErrorMessage() const {return "No method is defined to check if a day is business for the calendar given.";}
}