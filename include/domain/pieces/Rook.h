//
// Created by Daniel Stöcklein on 07.08.24.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(std::string name, Color color, Position position, Board *board);

    virtual ~Rook();

    bool isMoveValid(Move *move) override;
};


#endif //CHESS_ROOK_H
