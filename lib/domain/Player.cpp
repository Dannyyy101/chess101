//
// Created by Daniel Stöcklein on 08.08.24.
//

#include <utility>

#include "../../include/domain/Player.h"

Player::Player(std::string name, Color color) : name_(std::move(name)), color_(color) {}

Player::~Player() = default;

Color Player::getColor() {
    return this->color_;
}

std::string Player::getName() {
    return this->name_;
}