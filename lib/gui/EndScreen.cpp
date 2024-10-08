//
// Created by Daniel Stöcklein on 10.08.24.
//

#include "../../include/gui/EndScreen.h"

EndScreen::EndScreen() {
    this->shape.setSize({300, 200});

    float x = static_cast<float>((WINDOW_SIZE / 2) - (this->shape.getSize().x / 2));
    float y = static_cast<float>((WINDOW_SIZE / 2) - (this->shape.getSize().y / 2));

    this->shape.setPosition({x, y});

    this->shape.setFillColor(sf::Color(241, 241, 241));

    if(!this->font.loadFromFile("resources/fonts/ARIAL.TTF")){
        std::cerr << "Font not found" << std::endl;
    }

    this->text.setFont(font);

}

EndScreen::~EndScreen() = default;

void EndScreen::draw(sf::RenderWindow& window, std::string winner, std::string gameEnding) {
    float x = static_cast<float>((WINDOW_SIZE / 2) - (this->shape.getSize().x / 2));
    float y = static_cast<float>((WINDOW_SIZE / 2) - (this->shape.getSize().y / 2));
    this->text.setFillColor(sf::Color::Black);
    this->text.setString(gameEnding + "\n" + winner);
    this->text.setPosition({
        x + (this->shape.getSize().x / 2) - (this->text.getGlobalBounds().getSize().x / 2),
        y + this->shape.getSize().y / 2 - (this->text.getGlobalBounds().getSize().y / 2)
    });
    window.draw(this->shape);
    window.draw(this->text);
}
