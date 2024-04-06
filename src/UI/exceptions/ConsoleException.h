#pragma once

#include <exception>

class ConsoleException: public std::exception {
protected:
    const char* message;

public:
    explicit ConsoleException(const char* message): message{message} {}

    const char* what() const noexcept override {return this->message;}
};
