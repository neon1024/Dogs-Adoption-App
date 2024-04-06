#pragma once

#include "../repository/Repository.h"
#include "../repository/FileRepository.h"
#include "exceptions/ServiceException.h"
#include "../UndoRedo/UndoRedo.h"

#include <vector>

class Service {
private:
    FileRepository* repository;
    FileRepository* userRepository;
    UndoRedo undo_redo;

public:
    Service();

    explicit Service(FileRepository* repository, FileRepository* userRepository);

    ~Service();

    void load_repository() const;
    void save_repository() const;

    std::string get_input_file_name() const;
    std::string get_output_file_name() const;

    /// Dogs ///
    std::vector<Dog>& get_dogs();
    unsigned long long int get_number_of_dogs();

    void add(std::string& breed, std::string& name, int& age, std::string& photograph, std::string& id);
    bool search_dogs(std::string& id) const;
    void update(std::string& id, std::string& new_breed, std::string& new_name, int& new_age, std::string& new_photograph);
    void remove(std::string& id);

    /// Adopted Dogs ///
    std::vector<Dog>& get_adopted_dogs();
    unsigned long long int get_number_of_adopted_dogs();

    bool search_adopted_dogs(const std::string& id);
    void adopt(Dog& dog);

    void undo();

    void redo();

    std::vector<Command>& get_undo_stack();

    std::vector<Command>& get_redo_stack();
};
