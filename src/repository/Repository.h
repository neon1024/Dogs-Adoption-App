#pragma once

#include "../domain/Dog.h"
#include "validators/DogValidator.h"

#include <vector>

class Repository {
protected:
    std::vector<Dog> data;
    DogValidator* validator;

public:
    Repository();
    explicit Repository(DogValidator* validator);

    std::vector<Dog>& get_data();
    unsigned long long int get_size() const;

    void add(std::string& breed, std::string& name, int& age, std::string& photograph, std::string& id);
    bool search(const std::string& id);
    void update(std::string& id, std::string& new_breed, std::string& new_name, int& new_age, std::string& new_photograph);
    void remove(std::string& id);
    Dog& get_entity_by_id(std::string& id);
};
