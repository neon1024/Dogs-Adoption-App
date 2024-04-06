#include "TestDog.h"
#include <cassert>

void TestDog::test_Dog() {
    Dog ghost{};

    assert(ghost.get_breed().empty());
    assert(ghost.get_name().empty());
    assert(ghost.get_age() == 0);
    assert(ghost.get_photograph().empty());
    assert(ghost.get_id().empty());

    std::string breed1 = "Golden Retriever";
    std::string name1 = "Goldy";
    int age1 = 5;
    std::string photograph1 = "link1";
    std::string id1 = "1";

    Dog dog1{breed1, name1, age1, photograph1, id1};

    assert(dog1.get_breed() == breed1);
    assert(dog1.get_name() == name1);
    assert(dog1.get_age() == age1);
    assert(dog1.get_photograph() == photograph1);
    assert(dog1.get_id() == id1);

    assert(dog1.toString() == "Breed: " + breed1 + ", Name: " + name1 + ", Age: " + std::to_string(age1) + ", ID: " + id1 + '\n');

    std::string breed2 = "Mastiff";
    std::string name2 = "Max";
    int age2 = 7;
    std::string photograph2 = "link2";
    std::string id2 = "2";

    dog1.set_breed(breed2);
    dog1.set_name(name2);
    dog1.set_age(age2);
    dog1.set_photograph(photograph2);
    dog1.set_id(id2);

    assert(dog1.get_breed() == breed2);
    assert(dog1.get_name() == name2);
    assert(dog1.get_age() == age2);
    assert(dog1.get_photograph() == photograph2);
    assert(dog1.get_id() == id2);

    assert(dog1.toString() == "Breed: " + breed2 + ", Name: " + name2 + ", Age: " + std::to_string(age2) + ", ID: " + id2 + '\n');
}
