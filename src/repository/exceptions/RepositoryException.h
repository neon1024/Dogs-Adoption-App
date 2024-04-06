#pragma once

#include <exception>

class RepositoryException: public std::exception {
protected:
    const char* message;

public:
    explicit RepositoryException(const char* message): message{message} {}

    const char* what() const noexcept override {return this->message;}
};
