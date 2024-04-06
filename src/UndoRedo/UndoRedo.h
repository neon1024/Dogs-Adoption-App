#pragma once

#include <iostream>

#include <vector>
#include "Command.h"

class UndoRedo {
private:
    std::vector<Command> undo_stack;
    std::vector<Command> redo_stack;

public:
    void push_to_undo(Command& command);

    Command& pop_from_undo();

    void push_to_redo(Command& command);

    Command& pop_from_redo();

    std::vector<Command>& get_undo_stack();

    std::vector<Command>& get_redo_stack();
};
