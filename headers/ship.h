#pragma once

#include "string"

class Ship {
public:
    Ship(int size, std::string type);
    int GetSize() const;

private:
    int size_;
    std::string type_; //ship_ type_
};
