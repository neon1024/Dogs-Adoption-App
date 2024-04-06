#include "MainGUI.h"

MainGUI::MainGUI(GUI *admin_GUI, GUI *user_GUI): admin_GUI{admin_GUI}, user_GUI{user_GUI} {
    this->initialize_GUI();
    this->connect_signals_and_slots();
}

void MainGUI::initialize_GUI() {
    this->choose_file_format_layout = new QVBoxLayout{};

    this->choose_GUI_layout = new QVBoxLayout{};

    /// set main layout
    setLayout(this->choose_GUI_layout);

    setWindowTitle("Dogs Adoption");

    resize(250, 100);

    /// choose GUI layout
    this->choose_GUI_label = new QLabel{"Choose mode"};
    this->choose_GUI_label->setAlignment(Qt::AlignCenter);
    this->choose_GUI_layout->addWidget(this->choose_GUI_label);

    this->run_admin_GUI_button = new QPushButton{"admin"};
    this->choose_GUI_layout->addWidget(this->run_admin_GUI_button);

    this->run_user_GUI_button = new QPushButton{"user"};
    this->choose_GUI_layout->addWidget(this->run_user_GUI_button);
}

void MainGUI::connect_signals_and_slots() {
    /// run admin GUI
    connect(this->run_admin_GUI_button, &QPushButton::clicked, this, [=](){
        this->admin_GUI->show();
    });

    /// run user GUI
    connect(this->run_user_GUI_button, &QPushButton::clicked, this, [=](){
        this->user_GUI->show();
    });
}
