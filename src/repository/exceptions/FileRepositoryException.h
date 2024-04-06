#pragma once

#include "RepositoryException.h"

class FileRepositoryException: public RepositoryException {
public:
    explicit FileRepositoryException(const char* message): RepositoryException{message} {}
};
