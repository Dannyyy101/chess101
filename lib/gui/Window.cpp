#include "../../include/gui/Window.h"
#include "../../include/gui/DecisionField.h"
#include "../../include/gui/EndScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Window::Window() = default;

Window::~Window() = default;

void Window::runWindow(Session *session, array<array<string, 8>, 8> * board) {
    std::array<GuiField *, 2> activeFields = {};
    int activeFieldsIndex = 0;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Chess");
    DecisionField field(300, 375, 200, 50, sf::Color::Black);
    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (session->needsPawnToEvolve()) {
                        std::array<int, 2> pos = session->getPositionFromPawnToEvolve();
                        field.setPosition({static_cast<float>(pos[0] * 100), static_cast<float>(pos[1] * 100)});
                        for (auto button: field.getDecisionButtons()) {
                            button->isPressed(window);
                        }
                    } else {
                        for (int i = 7; i >= 0; --i) {
                            for (int j = 7; j >= 0; --j) {
                                if (this->fields_[j][i]->isPressed(window)) {
                                    sf::RectangleShape &rect = fields_[j][i]->getShape();
                                    activeFields[activeFieldsIndex++] = fields_[j][i];

                                    std::array<float, 2> newPosition = {rect.getPosition().y, rect.getPosition().x};
                                    this->makeMove(session, newPosition);
                                    if (session->isMoveComplete()) {
                                        activeFields[0]->unFocus();
                                        activeFields[1]->unFocus();
                                        activeFieldsIndex = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            this->updateWindow(board);
        }

        window.clear(sf::Color::Transparent);

        for (int i = 7; i >= 0; --i) {
            for (int j = 0; j < 8; ++j) {
                this->fields_[j][i]->draw(window);
            }
        }
        if (session->needsPawnToEvolve()) {
            field.draw(window);
            int pieceIndex;
            if ((pieceIndex = field.getPieceIndex()) != -1) {
                session->changePawnTo(pieceIndex);
            }
        }


        window.display();

        if (session->hasError()) {
            std::string errorMessage = session->getError().getErrorMessage();
            if (errorMessage == "GAME OVER") {
                EndScreen endScreen;
                endScreen.draw(window, "GAME OVER");
                window.display();
                sf::Time t = sf::milliseconds(100000);
                sf::sleep(t);
                //window.close();
            }
            //this->displayError(errorMessage);
        }

    }

}

void Window::setUpWindow(array<array<string, 8>, 8> * board) {
    for (int i = 7; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            float x = j * 100;
            float y = i * 100;
            this->fields_[i][j] = new GuiField(x, y, 100, 100, (i + j) % 2 == 0);
            std::string field = (*board)[i][j];
            if (!field.empty()) {
                this->fields_[i][j]->changeImage(field);
            } else {
                this->fields_[i][j]->removeImage();
            }

        }
    }
}

void Window::updateWindow(array<array<string, 8>, 8> * board) {
    for (int i = 7; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            if (fields_[i][j] != nullptr) {
                std::string field = (*board)[i][j];
                if (!field.empty()) {
                    this->fields_[i][j]->changeImage(field);
                } else {
                    this->fields_[i][j]->removeImage();
                }
            }
        }
    }
}

void Window::makeMove(Session *session, std::array<float, 2> &newMove) {
    int y = newMove[0] / 100;
    int x = newMove[1] / 100;
    session->addPositionToMove({x, y});
}