#include "CSVFileRepository.h"


CSVFileRepository::CSVFileRepository(std::string &input_file_name, std::string &output_file_name, DogValidator* validator)
: FileRepository(input_file_name, output_file_name, validator) {}
