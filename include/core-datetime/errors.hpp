#pragma once 
#include <iostream>
#include <exception>

class DateTimeLibraryError: public std::exception 
{
    public:
        const char* what() const noexcept override;
        explicit DateTimeLibraryError(){};
        virtual ~DateTimeLibraryError() = default;
    protected: 
        virtual std::string getErrorMessage() const = 0; 
    private:
        mutable std::string cachedMessage_;  // must be mutable to modify in const what()
};


namespace DatetimeErrorRegistry {

    class InvalidCivilDateError final: public DateTimeLibraryError { protected: std::string getErrorMessage() const override; };

    class InvalidCivilHourError final: public DateTimeLibraryError { protected: std::string getErrorMessage() const override; };

    class InvalidDateStringFormatError final: public DateTimeLibraryError { protected: std::string getErrorMessage() const override; };

    class UnknownDayCountConventionError final: public DateTimeLibraryError { protected: std::string getErrorMessage() const override; };

    class InvalidStartEndDate final: public DateTimeLibraryError { protected: std::string getErrorMessage() const override; };

    class UnknownBusinessDayConventionError final: public DateTimeLibraryError { protected: std::string getErrorMessage() const override; };

    class UnknownHolidayCalendarError final: public DateTimeLibraryError { protected: std::string getErrorMessage() const override; };
}