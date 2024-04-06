#pragma once

#include <utility>
#include <vector>
#include <string>

class Command {
private:
    std::string name;
    std::vector<std::string> arguments;

public:
    Command(std::string& name, std::vector<std::string>& arguments) {
        this->name = name;
        this->arguments = arguments;
    }

    std::string& get_name();

    std::vector<std::string>& get_arguments();

    std::string toString();
};
