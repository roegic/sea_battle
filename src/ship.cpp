#pragma once

#include "../headers/ship.h"
#include "string"

Ship::Ship(int size, std::string type) : size_(size), type_(std::move(type)) {
}

bool Ship::IsSunk() const {
    return hits_ >= size_;
}

int Ship::GetSize() const {
    return size_;
}

void Ship::Hit() {
    if (hits_ < size_) {
        ++hits_;
    }
}
