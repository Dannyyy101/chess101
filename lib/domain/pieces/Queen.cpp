//
// Created by Daniel Stöcklein on 02.08.24.
//

#include "../../../include/domain/pieces/Queen.h"
#include "../../../include/domain/pieces/Bishop.h"
#include "../../../include/domain/pieces/Rook.h"

Queen::Queen(std::string name, Color color, Position position, Board *board) : Piece(name, color, position, board) {}

Queen::~Queen() = default;

bool Queen::isMoveValid(Move *move) {
    Position self = this->getPosition();

    Bishop bishop("queen", getColor(), self, getBoard());
    Rook rook("queen", getColor(), self, getBoard());

    bool valid = bishop.isMoveValid(move) || rook.isMoveValid(move);

    return valid;
}

