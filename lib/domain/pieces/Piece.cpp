#include <utility>

#include "../../../include/domain/pieces/Piece.h"
#include <iostream>

Piece::Piece(std::string name, const Color color, Position position,  Board * board) : name_(std::move(name)), color_(color), position_(position), board_(board), hasMoved(false)
{
}

Piece::~Piece()
{
}

void Piece::move(const Position& position) {
    if(!this->hasMoved){
        this->hasMoved = true;
    }
    this->position_ = position;
}

void Piece::setPosition(Position position) {
    this->position_ = position;
}

Position Piece::getPosition() {
    return this->position_;
}

std::string Piece::getName() {
    std::string color = (color_ == Color::BLACK) ? "black-" : "white-";

    return color + name_;
}

Color Piece::getColor() {
    return this->color_;
}

bool Piece::getHasMoved() const {
    return this->hasMoved;
}

Board * Piece::getBoard() {
    return this->board_;
}