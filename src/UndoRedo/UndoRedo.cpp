#include <stdexcept>
#include "UndoRedo.h"

void UndoRedo::push_to_undo(Command &command) {
    this->undo_stack.push_back(command);
}

Command& UndoRedo::pop_from_undo() {
    if(this->undo_stack.empty()) {
        throw std::runtime_error("[!] undo stack is empty");
    }

    Command& command = this->undo_stack[this->undo_stack.size() - 1];

    this->undo_stack.pop_back();

    return command;
}

void UndoRedo::push_to_redo(Command &command) {
    this->redo_stack.push_back(command);
}

Command& UndoRedo::pop_from_redo() {
    if(this->redo_stack.empty()) {
        throw std::runtime_error("[!] redo stack is empty");
    }

    Command& command = this->redo_stack[this->redo_stack.size() - 1];

    this->redo_stack.pop_back();

    return command;
}

std::vector<Command> &UndoRedo::get_undo_stack() {
    return this->undo_stack;
}

std::vector<Command> &UndoRedo::get_redo_stack() {
    return this->redo_stack;
}
