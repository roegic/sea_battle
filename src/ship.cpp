#pragma once

#include "../headers/ship.h"
#include "string"

Ship::Ship(int size, std::string type) : size_(size), type_(std::move(type)) {
}

int Ship::GetSize() const {
    return size_;
}

