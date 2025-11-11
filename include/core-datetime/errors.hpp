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
