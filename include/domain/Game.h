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

class Board;

class Game {
private:
    std::array<Player *, 2> players_{};
    Player * currentPlayer_;
    Board * board_;
public:
    Game();
    ~Game();
    bool isCurrentPlayerInCheckMade();
    bool isGameOver();
    void runGame(Move * move, Error * error);
    Board getBoard();
    void nextPlayer();
};


#endif //CHESS_GAME_H
