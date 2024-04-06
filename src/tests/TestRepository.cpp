#include "TestRepository.h"
#include <cassert>

void foo(Repository* repository) {
    std::string new_breed = "Husky";
    std::string new_name = "Snow";
    int new_age = 10;
    std::string new_photograph = "new link";
    std::string new_id = "2";

    repository->add(new_breed, new_name, new_age, new_photograph, new_id);
}

void TestRepository::test_add() {
    DogValidator* validator = new DogValidator{};
    Repository* repository = new Repository{validator};

    assert(repository->get_size() == 0);

    std::string breed = "Labrador";
    std::string name = "Goldy";
    int age = 5;
    std::string photograph = "link";
    std::string id = "1";

    repository->add(breed, name, age, photograph, id);

    assert(repository->get_size() == 1);

    assert(repository->get_data()[0].get_breed() == breed);
    assert(repository->get_data()[0].get_name() == name);
    assert(repository->get_data()[0].get_age() == age);
    assert(repository->get_data()[0].get_photograph() == photograph);

    foo(repository);

    assert(repository->get_size() == 2);

    assert(repository->get_data()[1].get_breed() == "Husky");
    assert(repository->get_data()[1].get_name() == "Snow");
    assert(repository->get_data()[1].get_age() == 10);
    assert(repository->get_data()[1].get_photograph() == "new link");
}

void TestRepository::test_update() {
    DogValidator* validator = new DogValidator{};
    Repository* repository = new Repository{validator};

    assert(repository->get_size() == 0);

    std::string breed = "Labrador";
    std::string name = "Goldy";
    int age = 5;
    std::string photograph = "link";
    std::string id = "1";

    repository->add(breed, name, age, photograph, id);

    assert(repository->get_size() == 1);

    std::string new_name = "Husky";
    std::string new_breed = "Snow";
    int new_age = 10;
    std::string new_photograph = "new link";

    repository->update(id, new_breed, new_name, new_age, new_photograph);

    assert(repository->get_size() == 1 );

    assert(repository->get_data()[0].get_breed() == new_breed);
    assert(repository->get_data()[0].get_name() == new_name);
    assert(repository->get_data()[0].get_age() == new_age);
    assert(repository->get_data()[0].get_photograph() == new_photograph);
}

void TestRepository::test_remove() {
    DogValidator* validator = new DogValidator{};
    Repository* repository = new Repository{validator};

    assert(repository->get_size() == 0);

    std::string breed = "Labrador";
    std::string name = "Goldy";
    int age = 5;
    std::string photograph = "link";
    std::string id = "1";

    repository->add(breed, name, age, photograph, id);

    assert(repository->get_size() == 1);

    assert(repository->get_data()[0].get_breed() == breed);
    assert(repository->get_data()[0].get_name() == name);
    assert(repository->get_data()[0].get_age() == age);
    assert(repository->get_data()[0].get_photograph() == photograph);

    repository->remove(id);

    assert(repository->get_size() == 0);
}

void TestRepository::test_search() {
    DogValidator* validator = new DogValidator{};
    Repository* repository = new Repository{validator};

    assert(repository->get_size() == 0);

    std::string breed = "Labrador";
    std::string name = "Goldy";
    int age = 5;
    std::string photograph = "link";
    std::string id = "1";

    repository->add(breed, name, age, photograph, id);

    assert(repository->get_size() == 1);

    assert(repository->get_data()[0].get_breed() == breed);
    assert(repository->get_data()[0].get_name() == name);
    assert(repository->get_data()[0].get_age() == age);
    assert(repository->get_data()[0].get_photograph() == photograph);

    assert(repository->search("1") == true);
    assert(repository->search("2") == false);
}
