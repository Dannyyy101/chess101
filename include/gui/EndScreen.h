//
// Created by Daniel Stöcklein on 10.08.24.
//

#ifndef CHESS_ENDSCREEN_H
#define CHESS_ENDSCREEN_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"

class EndScreen {
private:
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text;
public:
    EndScreen();
    ~EndScreen();
    void draw(sf::RenderWindow& window, std::string winner);
};


#endif //CHESS_ENDSCREEN_H
