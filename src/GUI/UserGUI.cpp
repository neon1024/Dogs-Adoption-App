#include <QMessageBox>
#include "UserGUI.h"
#include "../utilities/Utilities.h"
#include "windows.h"
#include "shellapi.h"
#include "AdminGUI.h"
#include "../repository/exceptions/RepositoryException.h"

UserGUI::UserGUI(Service *service): service{service} {
    this->initialize_GUI();
    this->update_adopted_dogs_list_widget();
    this->connect_signals_and_slots();
}

void UserGUI::initialize_GUI() {
    this->main_layout = new QHBoxLayout{};

    setLayout(this->main_layout);

    setWindowTitle("User mode");

    this->adopted_dogs_list_widget = new QListWidget{};
    this->main_layout->addWidget(this->adopted_dogs_list_widget);

    /// filter
    this->second_layout = new QVBoxLayout{};
    this->main_layout->addLayout(this->second_layout);

    this->filter_label = new QLabel{"Filter"};
    this->filter_label->setAlignment(Qt::AlignCenter);
    this->second_layout->addWidget(this->filter_label);

    this->filter_form_layout = new QFormLayout{};
    this->second_layout->addLayout(this->filter_form_layout);

    this->breed_line_edit = new QLineEdit{};
    this->filter_form_layout->addRow("breed", this->breed_line_edit);

    this->age_line_edit = new QLineEdit{};
    this->filter_form_layout->addRow("age", this->age_line_edit);

    this->filter_buttons_layout = new QHBoxLayout{};
    this->second_layout->addLayout(this->filter_buttons_layout);

    this->filter_button = new QPushButton{"filter"};
    this->filter_buttons_layout->addWidget(this->filter_button);

    this->remove_filter_button = new QPushButton{"remove filter"};
    this->filter_buttons_layout->addWidget(this->remove_filter_button);

    /// display dogs 1 by 1
    this->display_dogs_1_by_1_layout = new QVBoxLayout{};
    this->second_layout->addLayout(this->display_dogs_1_by_1_layout);

    this->display_dogs_1_by_1_button = new QPushButton{"display dogs to adopt"};
    this->display_dogs_1_by_1_layout->addWidget(this->display_dogs_1_by_1_button);

    this->dogs_list_widget = new QListWidget{};

    /// launch
    this->launch_layout = new QVBoxLayout{};
    this->second_layout->addLayout(this->launch_layout);

    this->launch_button = new QPushButton{"visualize data"};
    this->launch_layout->addWidget(this->launch_button);
}

void UserGUI::connect_signals_and_slots() {
    /// filter
    connect(this->filter_button, &QPushButton::clicked, this, [=](){
        this->adopted_dogs_list_widget->clear();

        const std::vector<Dog> dogs = this->service->get_adopted_dogs();

        for(const auto& dog: dogs) {
            if(dog.get_breed() == this->breed_line_edit->text().toStdString() && dog.get_age() <= this->age_line_edit->text().toInt()) {
                this->adopted_dogs_list_widget->addItem(QString::fromStdString(dog.toString()));
            }
        }

        this->adopted_dogs_list_widget->setCurrentRow(0);
    });

    /// remove filter
    connect(this->remove_filter_button, &QPushButton::clicked, this, [=](){
        this->update_adopted_dogs_list_widget();

        this->breed_line_edit->clear();
        this->age_line_edit->clear();
    });

    /// visualize data
    connect(this->launch_button, &QPushButton::clicked, this, &UserGUI::visualize_data);

    /// display dogs 1 by 1
    connect(this->display_dogs_1_by_1_button, &QPushButton::clicked, this, &UserGUI::display_dogs_1_by_1);
}

void UserGUI::update_adopted_dogs_list_widget() {
    this->adopted_dogs_list_widget->clear();

    const std::vector<Dog>& adopted_dogs = this->service->get_adopted_dogs();

    for(const auto& dog: adopted_dogs) {
        this->adopted_dogs_list_widget->addItem(QString::fromStdString(dog.toString()));
    }

    this->adopted_dogs_list_widget->setCurrentRow(0);
}

void UserGUI::display_dogs_1_by_1() {
    QWidget* window = new QWidget{};
    window->setWindowTitle("Adopt dogs");

    QHBoxLayout* layout = new QHBoxLayout{};
    window->setLayout(layout);

    layout->addWidget(this->dogs_list_widget);

    QVBoxLayout* buttons_layout = new QVBoxLayout{};
    layout->addLayout(buttons_layout);

    QPushButton* next_button = new QPushButton{"next"};
    buttons_layout->addWidget(next_button);

    QPushButton* adopt_button = new QPushButton{"adopt"};
    buttons_layout->addWidget(adopt_button);

    std::vector<Dog>& dogs = this->service->get_dogs();
    this->count = this->service->get_number_of_dogs();
    this->current = 0;

    dogs_list_widget->addItem(QString::fromStdString(dogs[this->current].toString()));
    this->dogs_list_widget->setCurrentRow(0);

    if(this->count != 0) {
        this->current = (this->current + 1) % this->count;

        if(this->current == 0) {
            this->dogs_list_widget->clear();
            this->dogs_list_widget->addItem(QString::fromStdString(dogs[this->current].toString()));
            this->current = (this->current + 1) % this->count;
            this->dogs_list_widget->setCurrentRow(0);
        }
    }

    /// adopt
    connect(adopt_button, &QPushButton::clicked, this, [this](){
        std::vector<Dog>& dogs = this->service->get_dogs();

        try {
            this->service->adopt(dogs[this->dogs_list_widget->currentRow()]);
            this->update_adopted_dogs_list_widget();

            std::string id_remove = dogs[this->dogs_list_widget->currentRow()].get_id();
            this->service->remove(id_remove);

            delete this->dogs_list_widget->takeItem(this->dogs_list_widget->currentRow());

            this->current--;
            this->count--;

            if(this->count != 0) {
                this->current = (this->current + 1) % this->count;
            }

            this->dogs_list_widget->setCurrentRow(0);

        } catch(RepositoryException& error) {
            QMessageBox::warning(this, "Error", error.what());
        }
    });

    /// next
    connect(next_button, &QPushButton::clicked, this, [this](){
        if(this->current == 0) {
            this->dogs_list_widget->clear();
        }

        std::vector<Dog>& dogs = this->service->get_dogs();

        this->dogs_list_widget->addItem(QString::fromStdString(dogs[this->current].toString()));

        std::string link = dogs[this->current].get_photograph();

        ShellExecute(nullptr, reinterpret_cast<LPCWSTR>("open"), reinterpret_cast<LPCWSTR>(link.c_str()), nullptr, nullptr, SW_SHOW);

        if(this->count != 0) {
            this->current = (this->current + 1) % this->count;
        }

        this->dogs_list_widget->setCurrentRow(0);
    });

    window->show();
}

void UserGUI::visualize_data() {
    std::string file_name = this->service->get_output_file_name();

    if (is_csv_file(file_name.c_str())) {
        launch_file_in_excel(file_name.c_str());
    } else {
        if (is_html_file(file_name.c_str())) {
            launch_file_in_html(file_name.c_str());
        } else {
            QMessageBox::critical(this, "Error", "Couldn't launch the application");
        }
    }
}
