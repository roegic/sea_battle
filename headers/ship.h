#pragma once

#include "string"

class Ship {
public:
    Ship(int size, std::string type);
    bool IsSunk() const;
    int GetSize() const;
    void Hit();

private:
    int size_;
    int hits_; //hits_ count
    std::string type_; //ship_ type_
};
