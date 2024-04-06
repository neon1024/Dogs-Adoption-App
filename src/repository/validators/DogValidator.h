#pragma once

#include <string>
#include <algorithm>

class DogValidator {
public:
    static bool validateBreed(const std::string& breed);

    static bool validateName(const std::string& name);

    static bool validateAge(const int& age);

    static bool validatePhotograph(const std::string& photograph);

    static bool validateId(const std::string& id);
};
