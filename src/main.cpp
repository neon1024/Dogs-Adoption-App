#include "UI/Console.h"
#include "service/Service.h"
#include "repository/Repository.h"

#include "repository/exceptions/FileRepositoryException.h"

#include "tests/tests.h"
#include "Windows.h"
#include "repository/CSVFileRepository.h"
#include "repository/HTMLFileRepository.h"
#include "GUI/AdminGUI.h"
#include "GUI/MainGUI.h"
#include "GUI/UserGUI.h"
#include "models/DogsModel.h"
#include "views/DogsTableView.h"

#include <iostream>
#include <fstream>
#include <string>

#include <QApplication>
#include <QWidget>
#include <QTableView>

#define FILE_OPTIONS "123"

void display_file_options() {
    std::cout << "1: use .txt file" <<'\n';
    std::cout << "2: use .csv file" <<'\n';
    std::cout << "3: use .html file" <<'\n';
}

char ask_for_file_option() {
    char option;

    while(true) {
        std::cout << "> ";
        std::cin >> option;

        if (strchr(FILE_OPTIONS, option) == nullptr) {
            std::cout << "[!] Invalid file option. Try again." << '\n';
        } else {
            return option;
        }
    }
}

int main(int, char**) {
    // TODO change the path for the Excel
    // TODO when switching files, re run the program in order for the files to be updated
    
    std::string input_file_name_admin_repository{};
    std::string output_file_name_admin_repository{};

    std::string input_file_name_user_repository{};
    std::string output_file_name_user_repository{};

    // TODO use unique pointers
    DogValidator validator{};
    FileRepository adminRepository{};
    FileRepository userRepository{};
    HTMLFileRepository HTMLadminRepository{};
    HTMLFileRepository HTMLuserRepository{};

    Service* service = nullptr;

    display_file_options();

    char file_option = ask_for_file_option();

    if(file_option == '1') {
        input_file_name_admin_repository = "../dogs.txt";
        output_file_name_admin_repository = "../dogs.txt";

        input_file_name_user_repository = "../adoption_list.txt";
        output_file_name_user_repository = "../adoption_list.txt";

        adminRepository = FileRepository{input_file_name_admin_repository, output_file_name_admin_repository, &validator};
        userRepository = FileRepository{input_file_name_user_repository, output_file_name_user_repository, &validator};

        service = new Service{&adminRepository, &userRepository};
    }

    if(file_option == '2') {
        input_file_name_admin_repository = "../dogs.txt";
        output_file_name_admin_repository = "../dogs.csv";

        input_file_name_user_repository = "../adoption_list.txt";
        output_file_name_user_repository = "../adoption_list.csv";

        adminRepository = CSVFileRepository{input_file_name_admin_repository, output_file_name_admin_repository, &validator};
        userRepository = CSVFileRepository{input_file_name_user_repository, output_file_name_user_repository, &validator};

        service = new Service{&adminRepository, &userRepository};
    }

    if(file_option == '3') {
            input_file_name_admin_repository = "../dogs.txt";
        output_file_name_admin_repository = "../dogs.html";

        input_file_name_user_repository = "../adoption_list.txt";
        output_file_name_user_repository = "../adoption_list.html";

        HTMLadminRepository = HTMLFileRepository{input_file_name_admin_repository, output_file_name_admin_repository, &validator};
        HTMLuserRepository = HTMLFileRepository{input_file_name_user_repository, output_file_name_user_repository, &validator};

        service = new Service{&adminRepository, &userRepository};
    }

    QApplication app{__argc, __argv};

    DogsModel* dogs_model = new DogsModel{adminRepository};

    AdminGUI* admin_gui = new AdminGUI{service, dogs_model};

    UserGUI* user_gui = new UserGUI{service};

    MainGUI* main_gui = new MainGUI{admin_gui, user_gui};

    main_gui->show();

    // TODO after show() is called the execution will continue immediately

    return QApplication::exec();
}
