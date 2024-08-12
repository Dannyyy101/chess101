//
// Created by Daniel Stöcklein on 02.08.24.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "Player.h"
#include "utils/Position.h"
#include "Board.h"
#include "utils/Move.h"
#include <array>
#include "utils/Error.h"
#include "../Session.h"

class Board;

class Game {
private:
    std::array<Player *, 2> players_{};
    Player * currentPlayer_;
    Board * board_;
    int stalemateCounter;
public:
    Game();
    ~Game();
    bool isCurrentPlayerInCheckMade();
    bool isGameOver();
    void runGame(Session * session);
    Board getBoard();
    void nextPlayer();
    void changePawn(Session * session);
};


#endif //CHESS_GAME_H
