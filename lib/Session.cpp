//
// Created by Daniel Stöcklein on 11.08.24.
//

#include <utility>

#include "../include/Session.h"

Session::Session() : pawnChange_(-1), gameRunning_(true) {}

Session::~Session() = default;

// Move functions
bool Session::isMoveValid() const {
    return true;
}

bool Session::isMoveComplete() const {
    return this->move.isMoveComplete();
}

void Session::addPositionToMove(std::array<int, 2> position) {
    this->move.addPosition({position[0], position[1]});
}

void Session::setMoveComplete() {
    this->move.setMoveComplete(true);
}

// Error functions
Error& Session::getError() {
    return this->error;
}

bool Session::hasError() const {
    return this->error.hasError_;
}

// Pawn switch

bool Session::hasPawnBeenChanged() const {
    return this->pawnChange_ != -1;
}

void Session::changePawnTo(int index) {
    this->pawnChange_ = index;
}

int Session::getPieceToChangeTo(){
    int index = this->pawnChange_;
    this->pawnChange_ = -1;
    return index;
}

void Session::setMoveValid(bool valid) {

}

void Session::setPositionFromPawnToEvolve(const Position& position) {
    this->positionFromPawnToEvolve_ = position;
}

bool Session::needsPawnToEvolve() const {
    return this->needsPawnToEvolve_;
}

std::array<int, 2> Session::getPositionFromPawnToEvolve() {
    return {this->positionFromPawnToEvolve_.getX(), this->positionFromPawnToEvolve_.getY()};
}

void Session::setNeedsPawnToEvolve(bool needsPawnToEvolve) {
    this->pawnChange_ = -1;
    this->needsPawnToEvolve_ = needsPawnToEvolve;
}

// END
std::string Session::getWinner() {
    return this->winner_;
}

void Session::setGameOver() {
    this->gameRunning_ = false;
}

void Session::setWinner(std::string winner) {
    this->winner_ = std::move(winner);
}

bool Session::isGameRunning() const {
    return this->gameRunning_;
}

std::string Session::howHasGameEnded() {
    return this->gameEnding_;
}

void Session::setGameEnding(std::string ending) {
    this->gameEnding_ = std::move(ending);
}
