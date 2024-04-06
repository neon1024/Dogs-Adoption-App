#pragma once

#include "FileRepository.h"

class HTMLFileRepository: public FileRepository {
public:
    HTMLFileRepository();

    HTMLFileRepository(std::string& input_file_name, std::string& output_file_name, DogValidator* validator);

    void save(std::string& file_name) override;
};
