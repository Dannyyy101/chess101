//
// Created by Daniel Stöcklein on 02.08.24.
//

#include "../../../include/domain/pieces/Bishop.h"

Bishop::Bishop(std::string name, Color color, Position position, Board *board) : Piece(name, color, position, board) {}

Bishop::~Bishop() = default;

bool Bishop::isMoveValid(Move *move) {
    Position self = this->getPosition();
    Position position = move->getMove()[1];
    Board * board = this->getBoard();

    if((std::abs(self.getX() - position.getX()) - std::abs(self.getY() - position.getY())) != 0){
        return false;
    }
    int xDirection = (self.getX() - position.getX()) > 0 ? -1 : 1;
    int yDirection = (self.getY() - position.getY()) > 0 ? -1 : 1;

    int x = self.getX() + xDirection;
    int y = self.getY() + yDirection;
    for (int i = 0; i < std::abs(self.getX() - position.getX()) - 1; ++i) {

        if(board->getField({x, y})->getPiece() != nullptr){
            return false;
        }
        x += xDirection;
        y += yDirection;
    }
    return true;
}

