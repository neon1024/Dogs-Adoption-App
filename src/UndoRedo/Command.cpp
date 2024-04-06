#include "Command.h"

std::string& Command::get_name() {
     return this->name;
}

std::vector<std::string>& Command::get_arguments() {
    return this->arguments;
}

std::string Command::toString() {
    std::string result;

    result = this->name;

    return result;
}
