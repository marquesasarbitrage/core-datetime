#pragma once
#include <iostream>
#include <exception>

class NegativeEpochTimestampError : public std::exception {
    public:
        explicit NegativeEpochTimestampError();
        const char* what() const noexcept override;
        std::string getMessageAsString() const;
    private: 
        std::string message_;
};

class InvalidDateFormatError : public std::exception {
    public:
        explicit InvalidDateFormatError(std::string format);
        const char* what() const noexcept override;
        std::string getMessageAsString() const;
    private: 
        std::string format_;
        std::string message_;
};

class InvalidDateValueError : public std::exception {
    public:
        explicit InvalidDateValueError(std::string date);
        const char* what() const noexcept override;
        std::string getMessageAsString() const;
    private: 
        std::string date_;
        std::string message_;
};




