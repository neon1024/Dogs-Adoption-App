#include "HTMLFileRepository.h"
#include "exceptions/FileRepositoryException.h"
#include "../utilities/Utilities.h"

#include <iostream>
#include <fstream>

HTMLFileRepository::HTMLFileRepository(std::string &input_file_name, std::string &output_file_name, DogValidator *validator)
: FileRepository(input_file_name, output_file_name, validator) {}

void HTMLFileRepository::save(std::string &file_name) {
    std::ofstream fout{file_name};

    if(! fout.is_open()) {
        throw FileRepositoryException("[!] Error on opening file at save");
    }

    if(! is_html_file(file_name.c_str())) {
        for(const auto& dog: this->data) {
            fout << dog;
        }
        return;
    }

    fout << "<!DOCTYPE html>" << '\n';
    fout << "<html lang=\"en\">" << '\n';
    fout << "<head>" << '\n';
    fout << '\t' << "<title>Dogs Adoption List</title>" << '\n';
    fout << "</head>" << '\n';
    fout << "<body>" << '\n';
    fout << "<table border=\"1\">" << '\n';
    fout << '\t' << "<tr>" << '\n';

    fout << '\t' << '\t' << "<td>Breed</td>" << '\n';
    fout << '\t' << '\t' << "<td>Name</td>" << '\n';
    fout << '\t' << '\t' << "<td>Age</td>" << '\n';
    fout << '\t' << '\t' << "<td>Photograph</td>" << '\n';
    fout << '\t' << '\t' << "<td>Id</td>" << '\n';
    fout << '\n';

    for(const auto& dog: this->data) {
        fout << '\t' << "<tr>" << '\n';
        fout << '\t' << '\t' << "<td>" << dog.get_breed() << "</td>" << '\n';
        fout << '\t' << '\t' << "<td>" << dog.get_name() << "</td>" << '\n';
        fout << '\t' << '\t' << "<td>" << dog.get_age() << "</td>" << '\n';
        fout << '\t' << '\t' << "<td>" << "<a href=\"" << dog.get_photograph() << "\">" << "link" << "</a>" << "</td>" << '\n';
        fout << '\t' << '\t' << "<td>" << dog.get_id() << "</td>" << '\n';
        fout << '\t' << "</tr>" << '\n';
        fout << '\n';
    }

    fout << '\t' << "</tr>" << '\n';
    fout << "</table>" << '\n';
    fout << "</body>" << '\n';
    fout << "</html>" << '\n';

    fout.close();
}

HTMLFileRepository::HTMLFileRepository(): FileRepository{} {}
