//
// Created by Daniel Stöcklein on 08.08.24.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H


#include "Piece.h"

class King : public Piece {
public:
    King(std::string name, Color color, Position position, Board *board);

    virtual ~King();

    bool isMoveValid(Move *move) override;
};


#endif //CHESS_KING_H
