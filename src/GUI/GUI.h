#pragma once

#include <QWidget>

class GUI: public QWidget {
private:
    Q_OBJECT;

public:
    virtual void initialize_GUI() = 0;
    virtual void connect_signals_and_slots() = 0;
};
