#pragma once

#include "../repository/Repository.h"
#include "../domain/Dog.h"

class TestRepository {
public:
    void test_add();
    void test_update();
    void test_remove();
    void test_search();
};
