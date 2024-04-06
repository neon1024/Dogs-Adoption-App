#include "Dog.h"

#include <vector>
#include <iostream>

Dog::Dog(): breed{}, name{}, age{}, photograph{}, id{} {}

Dog::Dog(std::string& breed, std::string& name, int& age, std::string& photograph, std::string& id) {
    this->breed = breed;
    this->name = name;
    this->age = age;
    this->photograph = photograph;
    this->id = id;
}

/// Getters ///
std::string Dog::get_breed() const {
    return this->breed;
}

std::string Dog::get_name() const {
    return this->name;
}

int Dog::get_age() const {
    return this->age;
}

std::string Dog::get_photograph() const {
    return this->photograph;
}

std::string Dog::get_id() const {
    return this->id;
}

/// Setters ///
void Dog::set_breed(std::string& new_breed) {
    this->breed = new_breed;
}

void Dog::set_name(std::string& new_name) {
    this->name = new_name;
}

void Dog::set_age(int& new_age) {
    this->age = new_age;
}

void Dog::set_photograph(std::string& new_photograph) {
    this->photograph = new_photograph;
}

void Dog::set_id(std::string& new_id) {
    this->id = new_id;
}

/// Conversions ///
std::string Dog::toString() const {
    return "Breed: " + this->breed + ", Name: " + this->name + ", Age: " + std::to_string(this->age) + ", ID: " + this->id + '\n';
}

std::vector<std::string> tokenize(std::string str, char delim){
    std::vector<std::string> tokens;
    std::string temp = "";
    for(int i = 0; i < str.length(); i++){
        if(str[i] == delim){
            tokens.push_back(temp);
            temp = "";
        }
        else
            temp += str[i];
    }
    tokens.push_back(temp);
    return tokens;
}

std::istream& operator>>(std::istream& input_stream, Dog& dog) {
    std::string line;

    std::getline(input_stream, line);

    std::vector<std::string> tokens = tokenize(line, ',');

    if(tokens.size() != 5) {
        return input_stream;
    }

    dog.set_breed(tokens[0]);
    dog.set_name(tokens[1]);
    int age = stoi(tokens[2]);
    dog.set_age(age);
    dog.set_photograph(tokens[3]);
    dog.set_id(tokens[4]);

    return input_stream;
}

std::ostream& operator<<(std::ostream &os, const Dog &dog) {
    os << dog.breed << "," << dog.name << "," << dog.age << "," << dog.photograph << "," << dog.id << '\n';

    return os;
}
