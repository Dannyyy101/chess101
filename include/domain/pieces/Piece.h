#ifndef PIECE_H
#define PIECE_H

#include "../utils/Position.h"
#include "../utils/Color.h"
#include "../Board.h"
#include "../utils/Move.h"
#include <string>

class Board;

class Piece {
protected:
    const std::string name_;
    const Color color_;
    Position position_;
    Board *board_;
    bool hasMoved;

public:
    Piece(std::string name, Color color, Position position, Board *board);

    virtual ~Piece();

    void move(const Position &position);

    virtual bool isMoveValid(Move *move) = 0;

    void setPosition(Position position);

    Position getPosition();

    std::string getName();

    Color getColor();

    bool getHasMoved() const;

    Board *getBoard();
};


#endif