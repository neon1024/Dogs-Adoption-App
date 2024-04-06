#pragma once

#include <iostream>
#include <string>

class Dog {
private:
    std::string breed;
    std::string name;
    int age;
    std::string photograph;
    std::string id;

public:
    Dog();
    Dog(std::string& breed, std::string& name, int& age, std::string& photograph, std::string& id);

    /// Getters ///
    std::string get_breed() const;
    std::string get_name() const;
    int get_age() const;
    std::string get_photograph() const;
    std::string get_id() const;

    /// Setters ///
    void set_breed(std::string& new_breed);
    void set_name(std::string& new_name);
    void set_age(int& new_age);
    void set_photograph(std::string& new_photograph);
    void set_id(std::string& new_id);

    /// Conversions ///
    std::string toString() const;

    friend std::istream& operator>>(std::istream& is, Dog& dog);
    friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
};
