#pragma once

#include <exception>

class ServiceException: public std::exception {
protected:
    const char* message;

public:
    explicit ServiceException(const char* message): message{message} {}

    const char* what() const noexcept override {return this->message;}
};
