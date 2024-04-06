#include "Console.h"
#include <iostream>
#include <cstring>

#include <vector>
#include <algorithm>

#include "Windows.h"
#include "../repository/exceptions/RepositoryException.h"
#include "../utilities/Utilities.h"

#include <shellapi.h>

#define CONSOLE_MODES  "12x"
#define CONSOLE_OPTIONS "1234x"

Console::Console(Service* service): service{service} {}

/// Get User Input ///
char Console::get_console_mode() {
    char mode;

    std::cin >> mode;

    if(strchr(CONSOLE_MODES, mode) == nullptr) {
        throw ConsoleException("[!] Invalid console mode");
    }

    return mode;
}

char Console::get_console_option() {
    char option;

    std::cin >> option;

    if(strchr(CONSOLE_OPTIONS, option) == nullptr) {
        throw ConsoleException("[!] Invalid console option");
    }

    return option;
}

std::string Console::get_dog_breed() {
    std::string breed;

    std::cout << "breed: ";
    // dummy getline() to read '\n'
    std::getline(std::cin, breed);
    std::getline(std::cin, breed);

    return breed;
}

std::string Console::get_dog_name() {
    std::string name;

    std::cout << "name: ";

    std::getline(std::cin, name);

    return name;
}

int Console::get_dog_age() {
    std::string age{};

    std::cout << "age: ";
    std::cin >> age;

    if(std::all_of(age.begin(), age.end(), isdigit) and age[0] != '0') {
        return stoi(age);
    }

    throw ConsoleException("[!] Invalid dog age");
}

std::string Console::get_dog_photograph() {
    std::string photograph;

    std::cout << "photograph: ";
    std::cin >> photograph;

    return photograph;
}

std::string Console::get_dog_id() {
    std::string id;

    std::cout << "id: ";
    std::cin >> id;

    return id;
}

bool Console::ask_to_adopt() {
    std::string input;

    while(true) {
        std::cout << "adopt ? [y/n]: ";
        std::cin >> input;

        if(input == "y") {
            return true;
        } else {
            if(input == "n") {
                return false;
            } else {
                std::cout << "[!] Invalid Input. Try Again" << '\n';
            }
        }
    }
}

bool Console::ask_for_next() {
    std::string input;

    while(true) {
        std::cout << "next ? [y/n]: ";
        std::cin >> input;

        if(input == "y") {
            return true;
        } else {
            if(input == "n") {
                return false;
            } else {
                std::cout << "[!] Invalid Input. Try Again" << '\n';
            }
        }
    }
}

/// Service Operations ///
void Console::add_dog() {
    std::string breed = get_dog_breed();
    std::string name = get_dog_name();
    int age = get_dog_age();
    std::string photograph = get_dog_photograph();
    std::string id = get_dog_id();

    try {
        this->service->add(breed, name, age, photograph, id);

    } catch(RepositoryException& error) {
        std::cerr << error.what() << '\n';
    } catch(...) {
        std::cerr << "Unknown error in Console from Repository" << '\n';
    }
}

void Console::display_dogs() {
    std::vector<Dog>& dogs = this->service->get_dogs();

    for(const auto& dog: dogs) {
        std::cout << dog;
    }
}

void Console::update_dog() {
    std::string id = get_dog_id();
    std::string new_breed = get_dog_breed();
    std::string new_name = get_dog_name();
    int new_age = get_dog_age();
    std::string new_photograph = get_dog_photograph();

    try {
        this->service->update(id, new_breed, new_name, new_age, new_photograph);

    } catch(RepositoryException& error) {
        std::cerr << error.what() << '\n';
    } catch(...) {
        std::cerr << "Unknown error in Console from Repository" << '\n';
    }
}

void Console::remove_dog() {
    std::string id = get_dog_id();

    try {
        this->service->remove(id);

    } catch(RepositoryException& error) {
        std::cerr << error.what() << '\n';
    } catch(...) {
        std::cerr << "Unknown error in Console from Repository" << '\n';
    }
}

// TODO use filter from vector
void Console::display_dogs_one_by_one() {
    std::vector<Dog>& dogs = this->service->get_dogs();
    unsigned long long int number_of_dogs = this->service->get_number_of_dogs();

    for(unsigned long long int i = 0; i < number_of_dogs; i = (i + 1)%number_of_dogs) {
        std::cout << dogs[i];

        std::string link = dogs[i].get_photograph();

        ShellExecute(nullptr, reinterpret_cast<LPCWSTR>("open"), reinterpret_cast<LPCWSTR>(link.c_str()), nullptr, nullptr, SW_SHOW);

        bool adopt = ask_to_adopt();

        if(adopt) {
            try {
                this->service->adopt(dogs[i]);
                std::string id_remove = dogs[i].get_id();
                this->service->remove(id_remove);
                i--;
                number_of_dogs--;

            } catch(RepositoryException& error) {
                std::cerr << error.what() << '\n';
            } catch(...) {
                std::cerr << "Unknown error in Console from Repository" << '\n';
            }
            
        } else {
            bool next = ask_for_next();

            if(next) {
                continue;
            } else {
                break;
            }
        }

        if(number_of_dogs == 0) {
            break;
        }
    }
}

void Console::display_dogs_by_breed_having_age_less_than() {
    std::string breed = get_dog_breed();
    int age = get_dog_age();

    std::vector<Dog>& dogs = this->service->get_dogs();
    auto number_of_dogs = this->service->get_number_of_dogs();

    if(breed == ".") {
        bool adopt{};
        bool next{};

        for(unsigned long long int i = 0; i < number_of_dogs; i = (i + 1)%number_of_dogs) {
            if(dogs[i].get_age() < age) {
                std::cout << dogs[i].toString();

                std::string link = dogs[i].get_photograph();

                ShellExecute(nullptr, reinterpret_cast<LPCWSTR>("open"), reinterpret_cast<LPCWSTR>(link.c_str()), nullptr, nullptr, SW_SHOW);

                adopt = ask_to_adopt();

                if (adopt) {
                    try {
                        this->service->adopt(dogs[i]);
                        std::string id_remove = dogs[i].get_id();
                        this->service->remove(id_remove);
                        i--;
                        number_of_dogs--;

                    } catch(RepositoryException& error) {
                        std::cerr << error.what() << '\n';
                    } catch(...) {
                        std::cerr << "Unknown error in Console from Repository" << '\n';
                    }
                } else {
                    next = ask_for_next();

                    if (next) {
                        continue;
                    } else {
                        break;
                    }
                }
            } else {
                if(i == number_of_dogs - 1 && next == 0) {
                    break;
                }
            }
        }
    } else {
        bool adopt{};
        bool next{};

        for (auto i = 0; i < number_of_dogs; i = (i + 1) % number_of_dogs) {
            if (dogs[i].get_breed() == breed && dogs[i].get_age() < age) {
                std::cout << dogs[i];

                std::string link = dogs[i].get_photograph();

                ShellExecute(nullptr, reinterpret_cast<LPCWSTR>("open"), reinterpret_cast<LPCWSTR>(link.c_str()), nullptr, nullptr, SW_SHOW);

                adopt = ask_to_adopt();

                if(adopt) {
                    try {
                        this->service->adopt(dogs[i]);
                        std::string id_remove = dogs[i].get_id();
                        this->service->remove(id_remove);
                        i--;
                        number_of_dogs--;

                    } catch(RepositoryException& error) {
                        std::cerr << error.what() << '\n';
                    } catch(...) {
                        std::cerr << "Unknown error in Console from Repository" << '\n';
                    }

                } else {
                    next = ask_for_next();

                    if(next) {
                        continue;
                    } else {
                        break;
                    }
                }
            } else {
                if(i == number_of_dogs - 1 && next == 0) {
                    break;
                }
            }

            if(number_of_dogs == 0) {
                break;
            }
        }
    }
}

void Console::display_adoption_list() {
    std::vector<Dog> adopted_dogs = this->service->get_adopted_dogs();
    auto number_of_adopted_dogs = this->service->get_number_of_adopted_dogs();

    for(auto i = 0; i < number_of_adopted_dogs; ++i) {
        std::cout << adopted_dogs[i];
    }
}

void Console::display_adoption_list_in_the_corresponding_app() {
    std::string file_name = this->service->get_output_file_name();

    if (is_csv_file(file_name.c_str())) {
        launch_file_in_excel(file_name.c_str());
    } else {
        if (is_html_file(file_name.c_str())) {
            launch_file_in_html(file_name.c_str());
        } else {
            throw ConsoleException("[!] Error on file type check");
        }
    }
}

/// Display Console ///
void Console::display_console_modes() {
    std::cout << "1: admin mode" << '\n';
    std::cout << "2: user mode" << '\n';
    std::cout << "x: exit" << '\n';
}

void Console::display_admin_console_options() {
    std::cout << "1: add a dog" << '\n';
    std::cout << "2: update a dog" << '\n';
    std::cout << "3: remove a dog" << '\n';
    std::cout << "4: display all dogs" << '\n';
    std::cout << "x: exit" << '\n';
}

void Console::display_user_console_options() {
    std::cout << "1: display all dogs one by one" << '\n';
    std::cout << "2: display all dogs of a given breed, having an age less than a given number" << '\n';
    std::cout << "3: display the adoption list" << '\n';
    std::cout << "4: display the adoption list in the corresponding app" << '\n';
    std::cout << "x: exit" << '\n';
}

/// Run Console ///
void Console::run_console() {
    char chosen_mode{};

    while(true) {
        this->display_console_modes();

        try {
            chosen_mode = this->get_console_mode();

        } catch (ConsoleException& error) {
            std::cerr << error.what() << '\n';
        } catch(...) {
            std::cerr << "Unknown error in Console" << '\n';
        }

        switch (chosen_mode) {
            case '1':
                this->run_admin_console();
                break;

            case '2':
                this->run_user_console();
                break;

            case 'x':
                return;

            default:
                break;
        }
    }
}

void Console::run_admin_console() {
    char chosen_option{};

    while(true) {
        this->display_admin_console_options();

        try {
            chosen_option = this->get_console_option();

        } catch(ConsoleException& error) {
            std::cerr << error.what() << '\n';
        } catch(...) {
            std::cerr << "Unknown error in Console" << '\n';
        }

        switch (chosen_option) {
            case '1':
                try {
                    this->add_dog();

                } catch(ConsoleException& error) {
                    std::cerr << error.what() << '\n';
                } catch(...) {
                    std::cerr << "Unknown error in Console" << '\n';
                }

                break;

            case '2':
                try {
                    this->update_dog();

                } catch(ConsoleException& error) {
                    std::cerr << error.what() << '\n';
                } catch(...) {
                    std::cerr << "Unknown error in Console" << '\n';
                }

                break;

            case '3':
                try {
                    this->remove_dog();

                } catch(ConsoleException& error) {
                    std::cerr << error.what() << '\n';
                } catch(...) {
                    std::cerr << "Unknown error in Console" << '\n';
                }

                break;

            case '4':
                try {
                    this->display_dogs();
                } catch(ConsoleException& error) {
                    std::cerr << error.what() << '\n';
                } catch(...) {
                    std::cerr << "Unknown error in Console" << '\n';
                }

                break;

            case 'x':
                return;

            default:
                break;
        }
    }
}

void Console::run_user_console() {
    char chosen_option{};

    while(true) {
        this->display_user_console_options();

        try {
            chosen_option = this->get_console_option();

        } catch(ConsoleException& error) {
            std::cerr << error.what() << '\n';
        } catch(...) {
            std::cerr << "Unknown error in Console" << '\n';
        }

        switch(chosen_option) {
            case '1':
                try {
                    this->display_dogs_one_by_one();

                } catch(ConsoleException& error) {
                    std::cerr << error.what() << '\n';
                } catch(...) {
                    std::cerr << "Unknown error in Console" << '\n';
                }

                break;

            case '2':
                try {
                    this->display_dogs_by_breed_having_age_less_than();

                } catch(ConsoleException& error) {
                    std::cerr << error.what() << '\n';
                } catch(...) {
                    std::cerr << "Unknown error in Console" << '\n';
                }

                break;

            case '3':
                try {
                    this->display_adoption_list();

                } catch(ConsoleException& error) {
                    std::cerr << error.what() << '\n';
                } catch(...) {
                    std::cerr << "Unknown error in Console" << '\n';
                }

                break;

            case '4':
                try {
                    this->display_adoption_list_in_the_corresponding_app();

                } catch(ConsoleException& error) {
                    std::cerr << error.what() << '\n';
                } catch(...) {
                    std::cerr << "Unknown error in Console" << '\n';
                }

                break;

            case 'x':
                return;

            default:
                break;
        }
    }
}
