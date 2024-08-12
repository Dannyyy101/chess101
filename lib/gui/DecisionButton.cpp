//
// Created by Daniel Stöcklein on 10.08.24.
//

#include "../../include/gui/DecisionButton.h"

DecisionButton::DecisionButton(float x, float y, int width, int height, std::string image) : pressed_(false){
    this->shape.setPosition(x, y);
    this->shape.setSize({static_cast<float>(width), static_cast<float>(height)});
    if(!this->texture.loadFromFile(IMAGE_PATH + image + ".png")){
        std::cerr << "Image not found" << std::endl;
    }
    this->sprite.setTexture(texture);
    this->sprite.setPosition(this->shape.getPosition().x, this->shape.getPosition().y);
    this->sprite.setScale(
            this->shape.getSize().x / texture.getSize().x,
            this->shape.getSize().y / texture.getSize().y
    );
}

DecisionButton::~DecisionButton() = default;

void DecisionButton::draw(sf::RenderWindow &window) {
    window.draw(this->shape);
    window.draw(this->sprite);
}

bool DecisionButton::isPressed(sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = this->shape.getGlobalBounds();
    bool pressed = buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if(pressed){
        this->pressed_ = true;
    }
    return pressed;
}

bool DecisionButton::hasBeenPressed() const {
    return this->pressed_;
}