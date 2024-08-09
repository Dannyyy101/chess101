//
// Created by Daniel Stöcklein on 08.08.24.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <iostream>
#include <string>
#include "utils/Color.h"


class Player {
private:
    std::string name_;
    Color color_;
public:
    Player(std::string name, Color color);
    ~Player();
    Color getColor();
    std::string getName();
};


#endif //CHESS_PLAYER_H
