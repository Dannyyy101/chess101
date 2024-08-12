//
// Created by Daniel Stöcklein on 01.08.24.
//

#include "../../include/domain/Board.h"
#include "../../include/domain/pieces/Pawn.h"
#include "../../include/domain/pieces/Knight.h"
#include "../../include/domain/pieces/Bishop.h"
#include "../../include/domain/pieces/Rook.h"
#include "../../include/domain/pieces/Queen.h"
#include "../../include/domain/pieces/King.h"
#include <iostream>

Board::Board() : board_({}), fieldWithNames_(new array<array<std::string, 8>, 8>), kings_({}), lastMove_({}), lastPiece(nullptr){

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board_[i][j] = new Field(nullptr, (i + j) % 2 == 0 ? Color::WHITE : Color::BLACK);
        }
    }

    for (int i = 0; i < 8; ++i) {
        board_[1][i]->setPiece(new Pawn("pawn", Color::BLACK, Position(i, 1), this));
        board_[6][i]->setPiece(new Pawn("pawn", Color::WHITE, Position(i, 6), this));
    }

    board_[0][0]->setPiece(new Rook("rook", Color::BLACK, Position(0, 0), this));
    board_[0][1]->setPiece(new Knight("knight", Color::BLACK, Position(1, 0), this));
    board_[0][2]->setPiece(new Bishop("bishop", Color::BLACK, Position(2, 0), this));
    board_[0][3]->setPiece(new Queen("queen", Color::BLACK, Position(3, 0), this));
    board_[0][4]->setPiece(new King("king", Color::BLACK, Position(4, 0), this));
    board_[0][5]->setPiece(new Bishop("bishop", Color::BLACK, Position(5, 0), this));
    board_[0][6]->setPiece(new Knight("knight", Color::BLACK, Position(6, 0), this));
    board_[0][7]->setPiece(new Rook("rook", Color::BLACK, Position(7, 0), this));

    board_[7][0]->setPiece(new Rook("rook", Color::WHITE, Position(0, 7), this));
    board_[7][1]->setPiece(new Knight("knight", Color::WHITE, Position(1, 7), this));
    board_[7][2]->setPiece(new Bishop("bishop", Color::WHITE, Position(2, 7), this));
    board_[7][3]->setPiece(new King("king", Color::WHITE, Position(3, 7), this));
    board_[7][4]->setPiece(new Queen("queen", Color::WHITE, Position(4, 7), this));
    board_[7][5]->setPiece(new Bishop("bishop", Color::WHITE, Position(5, 7), this));
    board_[7][6]->setPiece(new Knight("knight", Color::WHITE, Position(6, 7), this));
    board_[7][7]->setPiece(new Rook("rook", Color::WHITE, Position(7, 7), this));

    kings_[0] = board_[7][3]->getPiece();
    kings_[1] = board_[0][4]->getPiece();
}

Board::~Board() {
    for (auto fields: board_) {
        for (auto field: fields) {
            delete field;
        }
    }
}

Field *Board::getField(const Position &position) {
    return this->board_[position.getY()][position.getX()];
}

b_size Board::getBoard() {
    return this->board_;
}

void Board::movePiece(Move *move) {
    std::array<Position, 2> m = move->getMove();
    Piece *piece = this->board_[m[0].getY()][m[0].getX()]->getPiece();
    move->setMoveComplete(false);

    piece->move(m[1]);

    this->lastMove_[0] = {m[0].getX(), m[0].getY()};
    this->lastMove_[1] = {m[1].getX(), m[1].getY()};
    this->lastPiece = this->board_[m[1].getY()][m[1].getX()]->getPiece();

    this->board_[m[0].getY()][m[0].getX()]->setPiece(nullptr);
    this->board_[m[1].getY()][m[1].getX()]->setPiece(piece);

    this->lastMove_[0] = {m[0].getX(), m[0].getY()};
    this->lastMove_[1] = {m[1].getX(), m[1].getY()};

    move->setMoveComplete(false);
    getFieldWithNames();
}

void Board::undoMove() {
    Piece *piece = this->board_[lastMove_[1].getY()][lastMove_[1].getX()]->getPiece();
    this->board_[lastMove_[0].getY()][lastMove_[0].getX()]->setPiece(piece);
    this->board_[lastMove_[1].getY()][lastMove_[1].getX()]->setPiece(this->lastPiece);
    if (piece) {
        piece->move(lastMove_[0]);
    }
    getFieldWithNames();
}

std::array<Piece *, 2> Board::getKings() {
    return this->kings_;
}

bool Board::isMoveEqualToOldMove(Move *move) {
    return this->lastMove_[0] == move->getMove()[0] && this->lastMove_[1] == move->getMove()[1];
}

array<array<string, 8>, 8> * Board::getFieldWithNames() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece * piece = this->board_[i][j]->getPiece();
            std::string field;
            if(piece){
                field = piece->getName();
            }
            (*this->fieldWithNames_)[i][j] = field;
        }
    }
    return this->fieldWithNames_;
}
