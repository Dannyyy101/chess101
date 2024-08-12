//
// Created by Daniel Stöcklein on 08.08.24.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "utils/Color.h"
#include "utils/Move.h"


class Player {
private:
    std::string name_;
    Color color_;
    std::vector<Move *> moves_;
public:
    Player(std::string name, Color color);

    ~Player();

    Color getColor();

    std::string getName();

    void addMove(Move *move);

    Move *getLastMove();
};


#endif //CHESS_PLAYER_H
