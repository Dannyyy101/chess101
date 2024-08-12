#include <utility>

#include "../../include/gui/GuiField.h"
#include <iostream>


GuiField::GuiField(float x, float y, int width, int height, int color) {

    if (color == 0) {
        this->color_ = sf::Color(235, 236, 208);
    } else if (color == 1) {
        this->color_ = sf::Color(119, 153, 84);
    }
    this->rect.setFillColor(this->color_);
    this->rect.setPosition(x, y);
    this->rect.setSize({static_cast<float>(width), static_cast<float>(height)});

}

GuiField::~GuiField() {
}

void GuiField::draw(sf::RenderWindow &window) {
    window.draw(this->rect);
    window.draw(this->sprite);
}

void GuiField::changeImage(const std::string &url) {
    this->imageUrl = url;
    const std::string &imagePath = IMAGE_PATH + url + ".png";
    if (!this->texture.loadFromFile(imagePath)) {
        std::cerr << "Error loading texture from file: " << imagePath << std::endl;
        return;
    }
    this->sprite.setTexture(texture);
    this->sprite.setPosition(this->rect.getPosition().x, this->rect.getPosition().y);
    this->sprite.setScale(
            this->rect.getSize().x / texture.getSize().x,
            this->rect.getSize().y / texture.getSize().y
    );
}

bool GuiField::isPressed(sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = rect.getGlobalBounds();
    bool contains = buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if(contains){
        this->rect.setFillColor(sf::Color(186, 201, 74));
    }
    return contains;
}

std::string GuiField::getImageUrl() {
    return this->imageUrl;
}

void GuiField::removeImage() {
    this->texture.create(100, 100);
}

sf::RectangleShape &GuiField::getShape() {
    return this->rect;
}

void GuiField::unFocus() {
    this->rect.setFillColor(this->color_);
}