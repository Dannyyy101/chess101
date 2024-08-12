//
// Created by Daniel Stöcklein on 03.08.24.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <array>
#include "Position.h"
#include <mutex>
class Move {
private:
    Position positionPiece;
    Position newPosition;
    bool isMoveComplete_;
    int index;
    mutable std::mutex mutex_;
public:
    Move();
    ~Move();
    void addPosition(const Position& position);
    void setMoveComplete(bool complete);
    bool isMoveComplete() const;
    std::array<Position, 2> getMove();
    bool operator==(const Move& other);
};


#endif //CHESS_MOVE_H
