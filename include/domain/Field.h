//
// Created by Daniel Stöcklein on 01.08.24.
//

#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H


#include "pieces/Piece.h"
#include <mutex>

class Piece;

class Field {
private:
    Piece * piece_;
    const Color color_;
    mutable std::mutex mutex_;
public:
    Field(Piece * piece, Color color);
    ~Field();

    Piece * getPiece();
    void setPiece(Piece * piece);

     Color getColor();
};


#endif //CHESS_FIELD_H
