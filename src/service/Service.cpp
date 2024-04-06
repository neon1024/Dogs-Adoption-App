#include "Service.h"

Service::Service(): repository{}, userRepository{} {
    this->load_repository();
}

Service::Service(FileRepository* repository, FileRepository* userRepository): repository{repository}, userRepository{userRepository} {
    this->load_repository();
}

std::string Service::get_input_file_name() const {
    return this->userRepository->get_input_file_name();
}

std::string Service::get_output_file_name() const {
    return this->userRepository->get_output_file_name();
}

void Service::load_repository() const {
    std::string input_file_name_admin_repository = this->repository->get_input_file_name();
    std::string input_file_name_user_repository = this->userRepository->get_input_file_name();

    this->repository->load(input_file_name_admin_repository);
    this->userRepository->load(input_file_name_user_repository);
}

void Service::save_repository() const {
    std::string input_file_name_admin_repository = this->repository->get_input_file_name();
    std::string output_file_name_admin_repository = this->repository->get_output_file_name();

    std::string input_file_name_user_repository = this->userRepository->get_input_file_name();
    std::string output_file_name_user_repository = this->userRepository->get_output_file_name();

    this->repository->save(output_file_name_admin_repository);
    this->repository->save(input_file_name_admin_repository);

    this->userRepository->save(output_file_name_user_repository);
    this->userRepository->save(input_file_name_user_repository);
}

/// Dogs ///
std::vector<Dog>& Service::get_dogs() {
    return this->repository->get_data();
}

unsigned long long int Service::get_number_of_dogs() {
    return this->repository->get_size();
}

void Service::add(std::string& breed, std::string& name, int& age, std::string& photograph, std::string& id) {
    this->repository->add(breed, name, age, photograph, id);
    this->save_repository();

    std::vector<std::string> arguments;

    arguments.push_back(breed);
    arguments.push_back(name);
    arguments.push_back(std::to_string(age));
    arguments.push_back(photograph);
    arguments.push_back(id);

    std::string command_name = "add";

    Command command{command_name, arguments};

    this->undo_redo.push_to_undo(command);
}

bool Service::search_dogs(std::string& id) const {
    return this->repository->search(id);
}

void Service::update(std::string& id, std::string& new_breed, std::string& new_name, int& new_age, std::string& new_photograph) {
    this->repository->update(id, new_breed, new_name, new_age, new_photograph);
    this->save_repository();

    std::vector<std::string> arguments;

    // TODO

    arguments.push_back(new_breed);
    arguments.push_back(new_name);
    arguments.push_back(std::to_string(new_age));
    arguments.push_back(new_photograph);
    arguments.push_back(id);

    std::string command_name = "update";

    Command command{command_name, arguments};

    this->undo_redo.push_to_undo(command);
}

void Service::remove(std::string& id) {
    auto dog = this->repository->get_entity_by_id(id);

    this->repository->remove(id);
    this->save_repository();

    std::vector<std::string> arguments;

    // TODO get the entity with the id and its data

    std::cout << "retrieved " << "id: " << dog.get_id() << '\n';

    arguments.push_back(dog.get_breed());
    arguments.push_back(dog.get_name());
    arguments.push_back(std::to_string(dog.get_age()));
    arguments.push_back(dog.get_photograph());
    arguments.push_back(id);

    std::string command_name = "remove";

    Command command{command_name, arguments};

    this->undo_redo.push_to_undo(command);
}

/// Adopted Dogs ///
std::vector<Dog>& Service::get_adopted_dogs() {
    return this->userRepository->get_data();
}

unsigned long long int Service::get_number_of_adopted_dogs() {
    return this->userRepository->get_size();
}

void Service::adopt(Dog& dog) {
    std::string breed = dog.get_breed();
    std::string name = dog.get_name();
    int age = dog.get_age();
    std::string photograph = dog.get_photograph();
    std::string id = dog.get_id();

    this->userRepository->add(breed, name, age, photograph, id);
}

bool Service::search_adopted_dogs(const std::string& id) {
    return this->userRepository->search(id);
}

Service::~Service() {
    this->save_repository();
}

void Service::undo() {
    try {
        Command& command = this->undo_redo.pop_from_undo();

        this->undo_redo.push_to_redo(command);

        const std::string& command_name = command.get_name();
        std::vector<std::string>& command_arguments = command.get_arguments();

        if (command_name == "add") {
            this->remove(command_arguments[4]);
            this->undo_redo.pop_from_undo();
            return;
        }

        if (command_name == "remove") {
            int age = stoi(command_arguments[2]);
            this->add(command_arguments[0], command_arguments[1], age, command_arguments[3], command_arguments[4]);
            this->undo_redo.pop_from_undo();
            return;
        }
    } catch(std::exception& error) {
        std::cout << error.what() << '\n';
    }
}

void Service::redo() {
    try {
        Command &command = this->undo_redo.pop_from_redo();

        const std::string &command_name = command.get_name();
        std::vector<std::string> command_arguments = command.get_arguments();

        if (command_name == "add") {
            int age = stoi(command_arguments[2]);
            std::cout << age << '\n';
            this->add(command_arguments[0], command_arguments[1], age, command_arguments[3], command_arguments[4]);
            return;
        }

        if (command_name == "remove") {
            this->remove(command_arguments[4]);
            return;
        }
    } catch(std::exception& error) {
        std::cout << error.what() << '\n';
    }
}

std::vector<Command> &Service::get_undo_stack() {
    return this->undo_redo.get_undo_stack();
}

std::vector<Command> &Service::get_redo_stack() {
    return this->undo_redo.get_redo_stack();
}
