#include "Repository.h"
#include "exceptions/RepositoryException.h"

#include <algorithm>

Repository::Repository(): data{}, validator{nullptr} {}

Repository::Repository(DogValidator *validator): validator{validator} {}

std::vector<Dog>& Repository::get_data() {
    return this->data;
}

unsigned long long int Repository::get_size() const {
    return this->data.size();
}

void Repository::add(std::string& breed, std::string& name, int& age, std::string& photograph, std::string& id) {
    if(! this->validator->validateBreed(breed)) {
        throw RepositoryException("[!] Invalid breed");
    }

    if(! this->validator->validateName(name)) {
        throw RepositoryException("[!] Invalid name");
    }

    if(! this->validator->validateAge(age)) {
        throw RepositoryException("[!] Invalid age");
    }

    if(! this->validator->validatePhotograph(photograph)) {
        throw RepositoryException("[!] Invalid photograph");
    }

    if(! this->validator->validateId(id)) {
        throw RepositoryException("[!] Invalid id");
    }

    if(std::any_of(this->data.begin(), this->data.end(), [&id] (const Dog& dog) {return dog.get_id() == id;})) {
        throw RepositoryException("[!] Entity already exist");
    }

    Dog dog{breed, name, age, photograph, id};

    this->data.push_back(dog);
}

bool Repository::search(const std::string& id) {
    if(! this->validator->validateId(id)) {
        throw RepositoryException("[!] Invalid Id");
    }

    return std::any_of(this->data.begin(), this->data.end(), [&id] (const Dog& dog) {return dog.get_id() == id;});
}

void Repository::update(std::string& id, std::string& new_breed, std::string& new_name, int& new_age, std::string& new_photograph) {
    if(! this->validator->validateId(id)) {
        throw RepositoryException("[!] Invalid Id");
    }

    if(! this->search(id)) {
        throw RepositoryException("[!] Entity doesn't exist");
    }

    for(auto& dog: this->data) {
        if(dog.get_id() == id) {
            dog.set_breed(new_breed);
            dog.set_name(new_name);
            dog.set_age(new_age);
            dog.set_photograph(new_photograph);
            break;
        }
    }
}

void Repository::remove(std::string& id) {
    if(! this->validator->validateId(id)) {
        throw RepositoryException("[!] Invalid Id");
    }

    if(! this->search(id)) {
        throw RepositoryException("[!] Entity doesn't exist");
    }

    int pos{};

    for(int i = 0; i < this->data.size(); ++i) {
        if(this->data[i].get_id() == id) {
            pos = i;
            break;
        }
    }

    this->data.erase(this->data.begin() + pos);
}

Dog& Repository::get_entity_by_id(std::string &id) {
    for(auto& dog: this->data) {
        if(dog.get_id() == id) {
            return dog;
        }
    }

    throw std::runtime_error("[!] Entity doesn't exist");
}
