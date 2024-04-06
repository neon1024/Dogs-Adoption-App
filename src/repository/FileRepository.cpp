#include "FileRepository.h"
#include "../repository/exceptions/FileRepositoryException.h"

#include <fstream>

FileRepository::FileRepository(): input_file_name{}, output_file_name{} {}

FileRepository::FileRepository(std::string &input_file_name, std::string &output_file_name, DogValidator *validator)
: Repository{validator}, input_file_name{input_file_name}, output_file_name{output_file_name} {
}

std::string FileRepository::get_input_file_name() const {
    return this->input_file_name;
}

std::string FileRepository::get_output_file_name() const {
    return this->output_file_name;
}

void FileRepository::load(std::string& file_name) {
    std::ifstream fin{file_name};

    if(! fin.is_open()) {
        throw FileRepositoryException("[!] Error on opening file at load");
    }

    Dog dog{};

    while(fin >> dog) {
        this->data.push_back(dog);
    }

    fin.close();
}

void FileRepository::save(std::string& file_name) {
    std::ofstream fout{file_name};

    if(! fout.is_open()) {
        throw FileRepositoryException("[!] Error on opening file at save");
    }

    for(const auto& dog: this->data) {
        fout << dog;
    }

    fout.close();
}
