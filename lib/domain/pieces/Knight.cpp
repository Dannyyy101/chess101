//
// Created by Daniel Stöcklein on 02.08.24.
//

#include "../../../include/domain/pieces/Knight.h"

Knight::Knight(std::string name, Color color, Position position, Board *board) : Piece(name, color, position, board) {}

Knight::~Knight() = default;

bool Knight::isMoveValid(Move *move) {
    Position self = this->getPosition();
    Position position = move->getMove()[1];

    if (std::abs(self.getY() - position.getY()) == 2){
        if(std::abs(self.getX() - position.getX()) == 1){
            return true;
        }
    }
    if (std::abs(self.getY() - position.getY()) == 1){
        if(std::abs(self.getX() - position.getX()) == 2){
            return true;
        }
    }
    return false;
}

