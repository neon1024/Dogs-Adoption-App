#include "Utilities.h"

#include <cstring>

#include "windows.h"
#include <shellapi.h>
#include <iostream>

bool is_csv_file(const char* file_name) {
    return stricmp(file_name + strlen(file_name) - 4, ".csv") == 0;
}

bool is_html_file(const char* file_name) {
    return stricmp(file_name + strlen(file_name) - 5, ".html") == 0;
}

void launch_file_in_excel(const char* file_name) {
    ShellExecuteA(nullptr, nullptr, EXCEL_PATH, file_name, nullptr, SW_SHOW);
}

void launch_file_in_html(const char* file_name) {
    std::string path = file_name;


    for(auto& character : path) {
        if(character == '/') {
            character = '\\';
        }
    }

    ShellExecuteA(nullptr, nullptr, path.c_str(), nullptr, nullptr, SW_SHOW);
}
