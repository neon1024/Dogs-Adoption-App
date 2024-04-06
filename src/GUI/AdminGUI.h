#pragma once

#include "GUI.h"
#include "../service/Service.h"

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QLabel>

class AdminGUI: public GUI {
private:
    Q_OBJECT;

    Service* service;

    QAbstractItemModel* model;
    QPushButton* model_button;

    QListWidget* dogs_list_widget;

    QLineEdit* breed_line_edit;
    QLineEdit* name_line_edit;
    QLineEdit* age_line_edit;
    QLineEdit* photograph_line_edit;
    QLineEdit* id_line_edit;

    QLabel* breed_label;
    QLabel* name_label;
    QLabel* age_label;
    QLabel* photograph_label;
    QLabel* id_label;

    QPushButton* add_dog_button;
    QPushButton* remove_dog_button;
    QPushButton* update_dog_button;

    QHBoxLayout* main_layout;
    QVBoxLayout* right_side_layout;
    QFormLayout* form_layout;
    QVBoxLayout* buttons_layout;

    QVBoxLayout* base_layout;

    QHBoxLayout* undo_redo_layout;
    QPushButton* undo_button;
    QPushButton* redo_button;

    QListWidget* undo_stack_list_widget;
    QListWidget* redo_stack_list_widget;

private:
    void fill_form();

    void clear_form();

    int get_index_of_selected_list_widget_item();

    std::string get_breed_from_list_widget_item_at_index(int index);
    std::string get_name_from_list_widget_item_at_index(int index);
    int get_age_from_list_widget_item_at_index(int index);
    std::string get_photograph_from_list_widget_item_at_index(int index);
    std::string get_id_from_list_widget_item_at_index(int index);

public:
    explicit AdminGUI(Service* service, QAbstractItemModel* model);

    void initialize_GUI() override;

    void update_dogs_list_widget();

    void connect_signals_and_slots() override;

    void add_dog();

    void update_dog();

    void remove_dog();

    void undo();

    void redo();

    void table_view();

    void update_undo_redo_stack_list_widget();

    public slots:
        void on_data_changed_signal();
};
