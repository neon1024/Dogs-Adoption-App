#pragma once

#include "../service/Service.h"
#include "exceptions/ConsoleException.h"

class Console {
private:
    Service* service;

    /// Service Operations ///
    void add_dog();
    void remove_dog();
    void update_dog();
    void display_dogs();

    void display_dogs_one_by_one();
    void display_dogs_by_breed_having_age_less_than();
    void display_adoption_list();

    void display_adoption_list_in_the_corresponding_app();

    /// Get User Input ///
    static char get_console_mode();
    static char get_console_option();

    static std::string get_dog_breed();
    static std::string get_dog_name();
    static int get_dog_age();
    static std::string get_dog_photograph();
    static std::string get_dog_id();

    static bool ask_to_adopt();
    static bool ask_for_next();

    /// Display Console ///
    static void display_console_modes();
    static void display_admin_console_options();
    static void display_user_console_options();

public:
    explicit Console(Service* service);

    /// Run Console ///
    void run_console();
    void run_admin_console();
    void run_user_console();
};
