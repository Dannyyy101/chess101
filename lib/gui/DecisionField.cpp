//
// Created by Daniel Stöcklein on 10.08.24.
//

#include "../../include/gui/DecisionField.h"


DecisionField::DecisionField(float x, float y, int width, int height, sf::Color color) {
    std::string pieceColor = color == sf::Color::Black ? "black-" : "white-";
    int buttonWidth = width / 4;
    buttons_[0] = new DecisionButton(x, y, buttonWidth, height, pieceColor + "queen");
    buttons_[1] = new DecisionButton(x + buttonWidth, y, buttonWidth, height, pieceColor + "knight");
    buttons_[2] = new DecisionButton(x + buttonWidth * 2, y, buttonWidth, height, pieceColor + "rook");
    buttons_[3] = new DecisionButton(x + buttonWidth * 3, y, buttonWidth, height, pieceColor + "bishop");
}

DecisionField::~DecisionField(){
    for(auto button : this->buttons_){
        delete button;
    }
}

void DecisionField::draw(sf::RenderWindow &window) {
    window.draw(this->shape);
    for(auto button : this->buttons_){
        button->draw(window);
    }
}

std::array<DecisionButton *, 4> DecisionField::getDecisionButtons() {
    return this->buttons_;
}

int DecisionField::getPieceIndex() {
    for (int i = 0; i < 4; ++i) {
        if(this->buttons_[i]->hasBeenPressed()){
            return i;
        }
    }
    return -1;
}

void DecisionField::setPosition(std::vector<float> position) {
    this->shape.setPosition({position[0], position[1]});
}
