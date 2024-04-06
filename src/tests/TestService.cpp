#include "TestService.h"
#include <cassert>

void TestService::test_add() {
//    DogValidator* validator = new DogValidator{};
//    auto* repository = new Repository{validator};
//    auto* userRepository = new FileRepository{validator};
//    auto* service = new Service{repository, userRepository};
//
//    assert(repository->get_size() == 0);
//
//    std::string breed1 = "Labrador";
//    std::string name1 = "Goldy";
//    int age1 = 5;
//    std::string photograph1 = "link";
//    std::string id1 = "1";
//
//    service->add(breed1, name1, age1, photograph1, id1);
//
//    assert(repository->get_size() == 1);
//    assert(service->get_number_of_dogs() == 1);
//    assert(service->search_dogs(id1) == true);
//
//    assert(repository->get_data()[0].get_breed() == breed1);
//    assert(repository->get_data()[0].get_name() == name1);
//    assert(repository->get_data()[0].get_age() == age1);
//    assert(repository->get_data()[0].get_photograph() == photograph1);
//
//    std::string breed2 = "Husky";
//    std::string name2 = "Snow";
//    int age2 = 10;
//    std::string photograph2 = "new link";
//    std::string id2 = "2";
//
//    service->add(breed2, name2, age2, photograph2, id2);
//
//    assert(repository->get_size() == 2);
//
//    assert(repository->get_data()[1].get_breed() == breed2);
//    assert(repository->get_data()[1].get_name() == name2);
//    assert(repository->get_data()[1].get_age() == age2);
//    assert(repository->get_data()[1].get_photograph() == photograph2);
}

void TestService::test_update() {
//    DogValidator* validator = new DogValidator{};
//    auto* repository = new Repository{validator};
//    auto* userRepository = new Repository{validator};
//    auto* service = new Service{repository, userRepository};
//
//    assert(repository->get_size() == 0);
//
//    std::string breed1 = "Labrador";
//    std::string name1 = "Goldy";
//    int age1 = 5;
//    std::string photograph1 = "link";
//    std::string id1 = "1";
//
//    service->add(breed1, name1, age1, photograph1, id1);
//
//    assert(repository->get_size() == 1);
//
//    assert(repository->get_data()[0].get_breed() == breed1);
//    assert(repository->get_data()[0].get_name() == name1);
//    assert(repository->get_data()[0].get_age() == age1);
//    assert(repository->get_data()[0].get_photograph() == photograph1);
//
//    std::string breed2 = "Husky";
//    std::string name2 = "Snow";
//    int age2 = 10;
//    std::string photograph2 = "new link";
//
//    service->update(id1, breed2, name2, age2, photograph2);
//
//    assert(repository->get_size() == 1);
//
//    assert(repository->get_data()[0].get_breed() == breed2);
//    assert(repository->get_data()[0].get_name() == name2);
//    assert(repository->get_data()[0].get_age() == age2);
//    assert(repository->get_data()[0].get_photograph() == photograph2);
}

void TestService::test_remove() {
//    DogValidator* validator = new DogValidator{};
//    auto* repository = new Repository{validator};
//    auto* userRepository = new Repository{validator};
//    auto* service = new Service{repository, userRepository};
//
//    assert(repository->get_size() == 0);
//
//    std::string breed1 = "Labrador";
//    std::string name1 = "Goldy";
//    int age1 = 5;
//    std::string photograph1 = "link";
//    std::string id1 = "1";
//
//    service->add(breed1, name1, age1, photograph1, id1);
//
//    assert(repository->get_size() == 1);
//
//    assert(repository->get_data()[0].get_breed() == breed1);
//    assert(repository->get_data()[0].get_name() == name1);
//    assert(repository->get_data()[0].get_age() == age1);
//    assert(repository->get_data()[0].get_photograph() == photograph1);
//
//    service->remove(id1);
//
//    assert(repository->get_size() == 0);
}

void TestService::test_userRepository() {
//    DogValidator* validator = new DogValidator{};
//    auto* repository = new Repository{validator};
//    auto* userRepository = new Repository{validator};
//    auto* service = new Service{repository, userRepository};
//
//    assert(service->get_number_of_adopted_dogs() == 0);
//
//    std::string breed;
//    std::string name;
//    int age;
//    std::string photograph;
//    std::string id;
//
//    breed = "Golden Retriever";
//    name = "Spike";
//    age = 3;
//    photograph = "https://marshallspetzone.com/blog/wp-content/uploads/2017/01/6.jpg";
//    id = "1";
//
//    Dog dog{breed, name, age, photograph, id};
//
//    service->adopt(dog);
//
//    assert(service->get_number_of_adopted_dogs() == 1);
//
//    assert(service->search_adopted_dogs(id) == true);
//
//    std::vector<Dog> dogs = service->get_dogs();
//    std::vector<Dog> adoption_list = service->get_adopted_dogs();
//
//    for(const auto& element: adoption_list) {
//        std::string element_id = element.get_id();
//        assert(service->search_adopted_dogs(element_id) == true);
//    }
}
