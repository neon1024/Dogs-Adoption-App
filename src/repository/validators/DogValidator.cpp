#include "DogValidator.h"

bool DogValidator::validateBreed(const std::string &breed) {
    if(breed.empty()) {
        return false;
    }

    return true;
}

bool DogValidator::validateName(const std::string &name) {
    if(name.empty()) {
        return false;
    }

    return true;
}

bool DogValidator::validateAge(const int &age) {
    if(age < 0) {
        return false;
    }

    return true;
}

bool DogValidator::validatePhotograph(const std::string &photograph) {
    if(photograph.empty()) {
        return false;
    }

    return true;
}

bool DogValidator::validateId(const std::string &id) {
    if(id.empty()) {
        return false;
    }

    return true;
}
