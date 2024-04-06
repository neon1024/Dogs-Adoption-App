#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "GUI.h"

class MainGUI: public GUI {
private:
    Q_OBJECT;

    GUI* admin_GUI;
    GUI* user_GUI;

    // TODO
    QVBoxLayout* choose_file_format_layout;
    QVBoxLayout* choose_GUI_layout;

    QLabel* choose_GUI_label;

    QPushButton* run_admin_GUI_button;
    QPushButton* run_user_GUI_button;

public:
    MainGUI(GUI* admin_GUI, GUI* user_GUI);

    void initialize_GUI() override;
    void connect_signals_and_slots() override;
};
