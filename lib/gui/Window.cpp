#include "../../include/gui/Window.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#define SIZE_OF_WINDOW 800

using namespace std;

Window::Window() = default;

Window::~Window() = default;

void Window::runWindow(Move *move, Error *error, Board *board) {
    std::array<GuiField *, 2> activeFields = {};
    int activeFieldsIndex = 0;

    sf::RenderWindow window(sf::VideoMode(SIZE_OF_WINDOW, SIZE_OF_WINDOW), "Chess");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 7; i >= 0; --i) {
                        for (int j = 7; j >= 0; --j) {
                            if (this->fields_[j][i]->isPressed(window)) {
                                sf::RectangleShape &rect = fields_[j][i]->getShape();
                                activeFields[activeFieldsIndex++] = fields_[j][i];

                                std::array<float, 2> newPosition = {rect.getPosition().y, rect.getPosition().x};
                                this->makeMove(move, newPosition);
                                if (move->isMoveComplete()) {
                                    activeFields[0]->unFocus();
                                    activeFields[1]->unFocus();
                                    activeFieldsIndex = 0;
                                }
                            }
                        }
                    }
                }
            }
            this->updateWindow(board->getBoard());
        }

        window.clear(sf::Color::Transparent);

        for (int i = 7; i >= 0; --i) {
            for (int j = 0; j < 8; ++j) {
                this->fields_[j][i]->draw(window);
            }
        }
        window.display();

        if (error->hasError()) {
            std::string errorMessage = error->getErrorMessage();
            if(errorMessage == "GAME OVER"){
                sf::Time t = sf::milliseconds(1000);
                sf::sleep(t);
                window.close();
            }
            //this->displayError(errorMessage);
        }

    }

}

void Window::setUpWindow(const b_size board) {
    for (int i = 7; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            unsigned x = j * 100;
            unsigned y = i * 100;
            this->fields_[i][j] = new GuiField(x, y, 100, 100, board[i][j]->getColor() == Color::WHITE);
            Piece *piece = board[i][j]->getPiece();
            if (piece != nullptr) {
                this->fields_[i][j]->changeImage(piece->getName());
            } else {
                this->fields_[i][j]->removeImage();
            }
        }
    }
}

void Window::updateWindow(b_size board) {
    for (int i = 7; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            if (fields_[i][j] != nullptr) {
                Piece *piece = board[i][j]->getPiece();
                if (piece != nullptr) {
                    this->fields_[i][j]->changeImage(piece->getName());
                } else {
                    this->fields_[i][j]->removeImage();
                }
            }
        }
    }
}

void Window::makeMove(Move *move, std::array<float, 2> &newMove) {
    int y = newMove[0] / 100;
    int x = newMove[1] / 100;
    move->addPosition({x, y});
}

void Window::displayError(const std::string &errorMessage) {
    // Create the popup window
    sf::RenderWindow window(sf::VideoMode(400, 200), "Error");
    sf::Text text;
    text.setString(errorMessage);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(50, 80);
    // Main loop to handle events and render the popup window
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }
}