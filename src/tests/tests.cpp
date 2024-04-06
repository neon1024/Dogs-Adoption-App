#include "tests.h"

void testAll() {
    TestDog test_Dog{};
    test_Dog.test_Dog();

    TestRepository test_Repository{};

    test_Repository.test_add();
    test_Repository.test_update();
    test_Repository.test_remove();
    test_Repository.test_search();

    TestService test_Service{};

    test_Service.test_add();
    test_Service.test_update();
    test_Service.test_remove();
    test_Service.test_userRepository();
}
