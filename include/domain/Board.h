//
// Created by Daniel Stöcklein on 01.08.24.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include "Field.h"
#include "utils/Color.h"
#include "utils/Position.h"
#include "../../include/domain/Game.h"
#include "../domain/utils/Move.h"
#include "pieces/Piece.h" // Full declaration of Piece

class Field;

class Piece;

using std::string, std::array;

typedef array<array<Field *, 8>, 8> b_size;

class Board {
private:
    b_size board_;
    array<array<string, 8>, 8> * fieldWithNames_;
    array<Piece *, 2> kings_;
    array<Position, 2> lastMove_;
    Piece *lastPiece;
public:
    Board();

    ~Board();

    Field *getField(const Position &position);

    b_size getBoard();

    bool isMoveEqualToOldMove(Move *move);

    void movePiece(Move *move);

    void undoMove();

    array<Piece *, 2> getKings();

    array<array<string, 8>, 8> * getFieldWithNames();
};


#endif //CHESS_BOARD_H
