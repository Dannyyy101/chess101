//
// Created by Daniel Stöcklein on 06.08.24.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "Piece.h"

class Knight : public Piece {
public:
    Knight(std::string name, Color color, Position position, Board *board);

    virtual ~Knight();

    bool isMoveValid(Move *move) override;
};


#endif //CHESS_KNIGHT_H
