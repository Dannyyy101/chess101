//
// Created by Daniel Stöcklein on 07.08.24.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(std::string name, Color color, Position position, Board *board);

    virtual ~Bishop();

    bool isMoveValid(Move *move) override;
};


#endif //CHESS_BISHOP_H
