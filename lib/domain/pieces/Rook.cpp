//
// Created by Daniel Stöcklein on 02.08.24.
//

#include "../../../include/domain/pieces/Rook.h"
#include <iostream>

Rook::Rook(std::string name, Color color, Position position, Board *board) : Piece(name, color, position, board) {}

Rook::~Rook() {}


bool Rook::isMoveValid(Move *move) {
    Position self = this->getPosition();
    Position position = move->getMove()[1];
    Board *board = this->getBoard();

    if ((std::abs(self.getX() - position.getX()) != 0) && (std::abs(self.getY() - position.getY())) != 0) {
        return false;
    }
    int xDirection = (self.getX() - position.getX()) > 0 ? -1 : 1;
    int yDirection = (self.getY() - position.getY()) > 0 ? -1 : 1;

    int x = self.getX();
    int y = self.getY();
    for (int i = 0;
         (i < std::abs(self.getX() - position.getX()) - 1) || (i < std::abs(self.getY() - position.getY()) - 1); ++i) {
        if (std::abs(self.getX() - position.getX()) != 0) {
            x += xDirection;
        } else {
            y += yDirection;
        }
        if (board->getField({x, y})->getPiece() != nullptr) {
            return false;
        }

    }
    return true;
}

