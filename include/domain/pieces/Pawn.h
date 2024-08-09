//
// Created by Daniel Stöcklein on 02.08.24.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H


#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(std::string name, Color color, const Position& position, Board *board);

    ~Pawn() override;

    bool isValidStraightMove(const Position& position, int direction);

    bool isMoveValid(Move *move) override;

};


#endif //CHESS_PAWN_H
