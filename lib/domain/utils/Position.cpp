#include "../../../include/domain/utils/Position.h"
#include <iostream>

Position::Position(int x, int y) : x(x), y(y) {
    if(x > MAX_SIZE || y > MAX_SIZE || x < MIN_SIZE || y < MIN_SIZE){
        throw std::runtime_error("Position not in field");
    }
}

Position::Position() : x(-1), y(-1) {}

Position::~Position() = default;

int Position::getX() const  {
    return this->x;
}

int Position::getY() const  {
    return this->y;
}

bool Position::operator==(const Position &obj) const{
    return obj.y == this->y && obj.x == this->x;
}
