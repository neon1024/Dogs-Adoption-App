#include <QMessageBox>
#include "AdminGUI.h"
#include "../views/DogsTableView.h"
#include "../repository/exceptions/RepositoryException.h"
#include "../models/DogsModel.h"

AdminGUI::AdminGUI(Service *service, QAbstractItemModel* model): service{service}, model{model} {
    this->initialize_GUI();
    this->update_dogs_list_widget();
    this->connect_signals_and_slots();
}

void AdminGUI::initialize_GUI() {
    this->base_layout = new QVBoxLayout{};

    // setting the window
    setLayout(this->base_layout);

    this->main_layout = new QHBoxLayout{};
    this->base_layout->addLayout(this->main_layout);

    setWindowTitle("Admin mode");

    this->dogs_list_widget = new QListWidget{};

    this->main_layout->addWidget(this->dogs_list_widget);

    this->breed_line_edit = new QLineEdit{};
    this->breed_label = new QLabel{"&breed"};
    this->breed_label->setBuddy(this->breed_line_edit);

    this->name_line_edit = new QLineEdit{};
    this->name_label = new QLabel{"&name"};
    this->name_label->setBuddy(this->name_line_edit);

    this->age_line_edit = new QLineEdit{};
    this->age_label = new QLabel{"&age"};
    this->age_label->setBuddy(this->age_line_edit);

    this->photograph_line_edit = new QLineEdit{};
    this->photograph_label = new QLabel{"&photograph"};
    this->photograph_label->setBuddy(this->photograph_line_edit);

    this->id_line_edit = new QLineEdit{};
    this->id_label = new QLabel{"&id"};
    this->id_label->setBuddy(this->id_line_edit);

    this->form_layout = new QFormLayout{};
    this->form_layout->addRow(this->breed_label, this->breed_line_edit);
    this->form_layout->addRow(this->name_label, this->name_line_edit);
    this->form_layout->addRow(this->age_label, this->age_line_edit);
    this->form_layout->addRow(this->photograph_label, this->photograph_line_edit);
    this->form_layout->addRow(this->id_label, this->id_line_edit);

    this->add_dog_button = new QPushButton{"add"};
    this->remove_dog_button = new QPushButton{"remove"};
    this->update_dog_button = new QPushButton{"update"};
    this->model_button = new QPushButton{"table view"};

    this->buttons_layout = new QVBoxLayout{};
    this->buttons_layout->addWidget(this->add_dog_button);
    this->buttons_layout->addWidget(this->update_dog_button);
    this->buttons_layout->addWidget(this->remove_dog_button);
    this->buttons_layout->addWidget(this->model_button);

    this->right_side_layout = new QVBoxLayout{};
    this->right_side_layout->addLayout(this->form_layout);
    this->right_side_layout->addLayout(this->buttons_layout);

    this->main_layout->addLayout(this->right_side_layout);

    this->undo_redo_layout = new QHBoxLayout{};

    this->undo_button = new QPushButton{"undo"};
    this->undo_redo_layout->addWidget(this->undo_button);

    this->redo_button = new QPushButton{"redo"};
    this->undo_redo_layout->addWidget(this->redo_button);

    this->base_layout->addLayout(this->undo_redo_layout);

    auto* undo_redo_stack_layout = new QHBoxLayout{};

    this->undo_stack_list_widget = new QListWidget{};
    undo_redo_stack_layout->addWidget(this->undo_stack_list_widget);

    this->redo_stack_list_widget = new QListWidget{};
    undo_redo_stack_layout->addWidget(this->redo_stack_list_widget);

    this->base_layout->addLayout(undo_redo_stack_layout);
}

void AdminGUI::update_dogs_list_widget() {
    // clear the list in order to update it
    this->dogs_list_widget->clear();

    // get the actual list of objects
    const std::vector<Dog>& dogs = this->service->get_dogs();

    // put the updated items in the list
    for(const auto& dog: dogs) {
        this->dogs_list_widget->addItem(QString::fromStdString(dog.toString()));
    }

    this->dogs_list_widget->setCurrentRow(0);
}

void AdminGUI::update_undo_redo_stack_list_widget() {
    std::vector<Command>& undo_stack = this->service->get_undo_stack();

    this->undo_stack_list_widget->clear();

    for(auto& command: undo_stack) {
        this->undo_stack_list_widget->addItem(QString::fromStdString(command.toString()));
    }

    std::vector<Command>& redo_stack = this->service->get_redo_stack();

    this->redo_stack_list_widget->clear();

    for(auto& command: redo_stack) {
        this->redo_stack_list_widget->addItem(QString::fromStdString(command.toString()));
    }
}

void AdminGUI::connect_signals_and_slots() {
    connect(this->add_dog_button, &QPushButton::clicked, this, &AdminGUI::add_dog);

    connect(this->update_dog_button, &QPushButton::clicked, this, &AdminGUI::update_dog);

    connect(this->remove_dog_button, &QPushButton::clicked, this, &AdminGUI::remove_dog);

    connect(this->undo_button, &QPushButton::clicked, this, &AdminGUI::undo);

    connect(this->redo_button, &QPushButton::clicked, this, &AdminGUI::redo);

    connect(this->model_button, &QPushButton::clicked, this, &AdminGUI::table_view);

    connect(reinterpret_cast<DogsModel*>(this->model), &DogsModel::data_changed_signal, this, &AdminGUI::on_data_changed_signal);

    connect(this->dogs_list_widget, &QListWidget::itemPressed, this, &AdminGUI::fill_form);
}

void AdminGUI::table_view() {
    DogsTableView* dogs_view = new DogsTableView{this->model};
    dogs_view->setWindowTitle("Dogs");
    dogs_view->show();
}

void AdminGUI::add_dog() {
    std::string breed = this->breed_line_edit->text().toStdString();
    std::string name = this->name_line_edit->text().toStdString();
    int age = this->age_line_edit->text().toInt();
    std::string photograph = this->photograph_line_edit->text().toStdString();
    std::string id = this->id_line_edit->text().toStdString();

    try {
        this->service->add(breed, name, age, photograph, id);
        this->clear_form();
        this->update_dogs_list_widget();

        // TODO undo redo stack list widget
        this->update_undo_redo_stack_list_widget();

    } catch(RepositoryException& error) {
//        auto *error_window = new QMessageBox{};
//        error_window->setText(error.what());
//        error_window->setWindowTitle("Error");
//        error_window->setIcon(QMessageBox::Critical);
//        error_window->exec();
        QMessageBox::critical(this, "Error", QString::fromStdString(error.what()));
    }
}

void AdminGUI::update_dog() {
    std::string breed = this->breed_line_edit->text().toStdString();
    std::string name = this->name_line_edit->text().toStdString();
    int age = this->age_line_edit->text().toInt();
    std::string photograph = this->photograph_line_edit->text().toStdString();
    std::string id = this->id_line_edit->text().toStdString();

//    QLineEdit* new_id_line_edit = new QLineEdit{};
//    QLabel* new_id_label = new QLabel{"&target id"};
//    new_id_label->setBuddy(new_id_line_edit);
//
//    QFormLayout* new_id_form = new QFormLayout{};
//    new_id_form->addRow(new_id_label, new_id_line_edit);
//
//    QPushButton* ok_button = new QPushButton{"ok"};
//
//    QWidget* new_id_window = new QWidget{};
//
//    QVBoxLayout* new_id_layout = new QVBoxLayout{new_id_window};
//    new_id_layout->addLayout(new_id_form);
//    new_id_layout->addWidget(ok_button);
//
//    new_id_window->show();

    try {
        std::string new_id = this->get_id_from_list_widget_item_at_index(this->get_index_of_selected_list_widget_item());
        this->service->update(new_id, breed, name, age, photograph);
        this->clear_form();
        this->update_dogs_list_widget();

        // TODO undo redo stack list widget
        this->update_undo_redo_stack_list_widget();

    } catch(RepositoryException& error) {
//        auto *error_window = new QMessageBox{};
//        error_window->setText(error.what());
//        error_window->setWindowTitle("Error");
//        error_window->setIcon(QMessageBox::Critical);
//        error_window->exec();
        QMessageBox::critical(this, "Error", QString::fromStdString(error.what()));
    }
}

void AdminGUI::remove_dog() {
    try {
        std::string remove_id = this->get_id_from_list_widget_item_at_index(this->get_index_of_selected_list_widget_item());
        this->service->remove(remove_id);
        this->update_dogs_list_widget();
        this->dogs_list_widget->setCurrentRow(0);
        this->clear_form();

        // TODO undo redo stack list widget
        this->update_undo_redo_stack_list_widget();

    } catch(RepositoryException& error) {
//        auto *error_window = new QMessageBox{};
//        error_window->setText(error.what());
//        error_window->setWindowTitle("Error");
//        error_window->setIcon(QMessageBox::Critical);
//        error_window->exec();
        QMessageBox::critical(this, "Error", QString::fromStdString(error.what()));
    }
}

void AdminGUI::fill_form() {
    int selected_row = this->dogs_list_widget->currentRow();
    this->breed_line_edit->setText(QString::fromStdString(this->get_breed_from_list_widget_item_at_index(selected_row)));
    this->name_line_edit->setText(QString::fromStdString(this->get_name_from_list_widget_item_at_index(selected_row)));
    this->age_line_edit->setText(QString::number(this->get_age_from_list_widget_item_at_index(selected_row)));
    this->photograph_line_edit->setText(QString::fromStdString(this->get_photograph_from_list_widget_item_at_index(selected_row)));
    this->id_line_edit->setText(QString::fromStdString(this->get_id_from_list_widget_item_at_index(selected_row)));
}

void AdminGUI::clear_form() {
    this->breed_line_edit->clear();
    this->name_line_edit->setText("");
    this->age_line_edit->setText("");
    this->photograph_line_edit->setText("");
    this->id_line_edit->setText("");
}

int AdminGUI::get_index_of_selected_list_widget_item() {
    return this->dogs_list_widget->currentRow();
}

std::string AdminGUI::get_breed_from_list_widget_item_at_index(int index) {
    std::vector<Dog>& dogs = this->service->get_dogs();

    return dogs[index].get_breed();
}

std::string AdminGUI::get_name_from_list_widget_item_at_index(int index) {
    std::vector<Dog>& dogs = this->service->get_dogs();

    return dogs[index].get_name();
}

int AdminGUI::get_age_from_list_widget_item_at_index(int index) {
    std::vector<Dog>& dogs = this->service->get_dogs();

    return dogs[index].get_age();
}

std::string AdminGUI::get_photograph_from_list_widget_item_at_index(int index) {
    std::vector<Dog>& dogs = this->service->get_dogs();

    return dogs[index].get_photograph();
}

std::string AdminGUI::get_id_from_list_widget_item_at_index(int index) {
    std::vector<Dog>& dogs = this->service->get_dogs();

    return dogs[index].get_id();
}

void AdminGUI::on_data_changed_signal() {
    this->update_dogs_list_widget();
}

void AdminGUI::undo() {
    this->service->undo();
    this->update_dogs_list_widget();

    // TODO undo redo stack list widget
    this->update_undo_redo_stack_list_widget();
}

void AdminGUI::redo() {
    this->service->redo();
    this->update_dogs_list_widget();

    // TODO undo redo stack list widget
    this->update_undo_redo_stack_list_widget();
}
