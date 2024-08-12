//
// Created by Daniel Stöcklein on 03.08.24.
//

#include "../../../include/domain/utils/Move.h"

Move::Move() : isMoveComplete_(false), index(0) {

}

Move::~Move() {

}

void Move::addPosition(const Position &position) {
    mutex_.lock();
    if (index == 0) {
        this->positionPiece = position;
        index++;
    } else if (index == 1) {
        this->newPosition = position;
        this->isMoveComplete_ = true;
        index++;
    } else {
        this->positionPiece = position;
        this->newPosition = Position();
        this->isMoveComplete_ = false;
        index = 1;
    }
    mutex_.unlock();
}

bool Move::isMoveComplete() const {
    return this->isMoveComplete_;
}

std::array<Position, 2> Move::getMove() {
    return {this->positionPiece, this->newPosition};
}

void Move::setMoveComplete(bool complete) {
   mutex_.lock();
    this->isMoveComplete_ = complete;
    mutex_.unlock();
}

bool Move::operator==(const Move &other) {
    return other.newPosition == this->newPosition && other.positionPiece == this->positionPiece;
}
