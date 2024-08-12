//
// Created by Daniel Stöcklein on 10.08.24.
//

#ifndef CHESS_DECISIONBUTTON_H
#define CHESS_DECISIONBUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"

class DecisionButton {
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Sprite sprite;
    bool pressed_;
public:
    DecisionButton(float x, float y, int width, int height, std::string image);
    ~DecisionButton();
    void draw(sf::RenderWindow& window);
    bool isPressed(sf::RenderWindow &window);
    bool hasBeenPressed() const;
};


#endif //CHESS_DECISIONBUTTON_H
