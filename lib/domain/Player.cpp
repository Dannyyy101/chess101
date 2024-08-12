//
// Created by Daniel Stöcklein on 08.08.24.
//

#include <utility>

#include "../../include/domain/Player.h"

Player::Player(std::string name, Color color) : name_(std::move(name)), color_(color), moves_({}) {}

Player::~Player() {
    for (auto move: this->moves_) {
        delete move;
    }
}

Color Player::getColor() {
    return this->color_;
}

std::string Player::getName() {
    return this->name_;
}

void Player::addMove(Move *move) {
    Move* m = new Move();
    m->addPosition(move->getMove()[0]);
    m->addPosition(move->getMove()[1]);
    this->moves_.push_back(m);
}

Move *Player::getLastMove() {
    if (this->moves_.size() > 1) {
        return this->moves_.at(moves_.size() - 2);
    } else {
        return nullptr;
    }
}