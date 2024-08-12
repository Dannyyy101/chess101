//
// Created by Daniel Stöcklein on 11.08.24.
//

#ifndef CHESS_SESSION_H
#define CHESS_SESSION_H


#include "domain/utils/Error.h"
#include "domain/utils/Move.h"

class Session {
private:
    int pawnChange_;
    Position positionFromPawnToEvolve_;
    bool needsPawnToEvolve_;
public:
    Error error;
    Move move;
    Session();

    ~Session();

    Error& getError();

    bool hasError() const;

    bool isMoveComplete() const;

    bool isMoveValid() const;

    void addPositionToMove(std::array<int, 2> position);

    void setMoveComplete();

    void setMoveValid(bool valid);

    bool hasPawnBeenChanged() const;

    void changePawnTo(int index);

    void setPositionFromPawnToEvolve(const Position& position);

    bool needsPawnToEvolve();

    void setNeedsPawnToEvolve(bool needsPawnToEvolve);

    std::array<int, 2> getPositionFromPawnToEvolve();

    int getPieceToChangeTo();
};


#endif //CHESS_SESSION_H
