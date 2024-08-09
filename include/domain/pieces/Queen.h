//
// Created by Daniel Stöcklein on 07.08.24.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(std::string name, Color color, Position position, Board *board);

    virtual ~Queen();

    bool isMoveValid(Move *move) override;
};


#endif //CHESS_QUEEN_H
