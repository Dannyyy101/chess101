//
// Created by Daniel Stöcklein on 01.08.24.
//

#include "../../include/domain/Field.h"

Field::Field(Piece *piece, Color color) : piece_(piece), color_(color) {}

Field::~Field() {
    delete piece_;
}

Piece *Field::getPiece() {
    std::lock_guard<std::mutex> guard(mutex_);
    return this->piece_;
}

void Field::setPiece(Piece *piece) {
    std::lock_guard<std::mutex> guard(mutex_);
    this->piece_ = piece;
}

Color Field::getColor() {
    return this->color_;
}