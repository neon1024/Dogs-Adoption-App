#pragma once

#include <QListWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include "GUI.h"
#include "../service/Service.h"

class UserGUI: public GUI {
private:
    Q_OBJECT;

    Service* service;

    QHBoxLayout* main_layout;
    QListWidget* adopted_dogs_list_widget;

    /// filter
    QVBoxLayout* second_layout;
    QLabel* filter_label;
    QFormLayout* filter_form_layout;
    QLineEdit* breed_line_edit;
    QLineEdit* age_line_edit;
    QHBoxLayout* filter_buttons_layout;
    QPushButton* filter_button;
    QPushButton* remove_filter_button;

    // display dogs 1 by 1
    QVBoxLayout* display_dogs_1_by_1_layout;
    QPushButton* display_dogs_1_by_1_button;

    QListWidget* dogs_list_widget;

    unsigned long long current;
    unsigned long long count;

    // launch
    QVBoxLayout* launch_layout;
    QPushButton* launch_button;

public:
    explicit UserGUI(Service* service);

    void initialize_GUI() override;
    void connect_signals_and_slots() override;
    void update_adopted_dogs_list_widget();
    void display_dogs_1_by_1();
    void visualize_data();
};
