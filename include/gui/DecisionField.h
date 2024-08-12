//
// Created by Daniel Stöcklein on 10.08.24.
//

#ifndef CHESS_DECISIONFIELD_H
#define CHESS_DECISIONFIELD_H

#include "../../include/gui/DecisionButton.h"


class DecisionField {
private:
    sf::RectangleShape shape;
    std::array<DecisionButton *, 4> buttons_{};
public:
    DecisionField(float x, float y, int width, int height, sf::Color color);
    ~DecisionField();

    std::array<DecisionButton *, 4> getDecisionButtons();

    void draw(sf::RenderWindow& window);
    int getPieceIndex();
    void setPosition(std::vector<float> position);
};


#endif //CHESS_DECISIONFIELD_H
