#pragma once

#include "FileRepository.h"

class CSVFileRepository: public FileRepository {
public:
    CSVFileRepository(std::string& input_file_name, std::string& output_file_name, DogValidator* validator);
};
