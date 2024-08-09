//
// Created by Daniel Stöcklein on 02.08.24.
//

#include "../../../include/domain/pieces/Pawn.h"
#include <iostream>
#include <utility>

Pawn::Pawn(std::string name, Color color, const Position &position, Board *board) : Piece(std::move(name), color,
                                                                                          position, board) {}

Pawn::~Pawn() = default;

bool Pawn::isValidStraightMove(const Position &position, int direction) {
    int xOffset = position.getX() - this->position_.getX();
    int yOffset = position.getY() - this->position_.getY();

    Piece *targetPiece = this->board_->getBoard()[position.getY()][position.getX()]->getPiece();
    if (targetPiece) {
        return (std::abs(xOffset) == 1 && yOffset == direction);
    } else {
        if (xOffset == 0 && yOffset == direction) {
            return true;
        }
        if (!this->hasMoved && xOffset == 0 && yOffset == 2 * direction) {
            return true;
        }
    }

    return false;
}

bool Pawn::isMoveValid(Move *move) {
    int direction = this->color_ == Color::WHITE ? 1 : -1;
    return isValidStraightMove(move->getMove()[1], direction);
}

