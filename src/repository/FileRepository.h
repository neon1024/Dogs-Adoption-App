#pragma once

#include "Repository.h"

class FileRepository: public Repository {
protected:
    std::string input_file_name;
    std::string output_file_name;

public:
    FileRepository();

    FileRepository(std::string &input_file_name, std::string &output_file_name, DogValidator *validator);

    std::string get_input_file_name() const;

    std::string get_output_file_name() const;

    virtual void load(std::string& file_name);

    virtual void save(std::string& file_name);
};
