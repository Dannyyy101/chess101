//
// Created by Daniel Stöcklein on 02.08.24.
//

#include "../../include/domain/Game.h"
#include "../../include/domain/Player.h"
#include "../../include/domain/pieces/King.h"
#include <iostream>

Game::Game() : board_(new Board()) {
    this->players_[0] = new Player("Daniel", Color::WHITE);
    this->players_[1] = new Player("Felix", Color::BLACK);
    this->currentPlayer_ = players_[0];
}

Game::~Game() {
    delete board_;
    delete players_[0];
    delete players_[1];
}

Board Game::getBoard() {
    return *this->board_;
}

void Game::nextPlayer() {
    if (this->currentPlayer_->getColor() == Color::WHITE) {
        this->currentPlayer_ = this->players_[1];
    } else {
        this->currentPlayer_ = this->players_[0];
    }
}

void Game::runGame(Move *move, Error *error) {
    bool gameRunning = true;
    while (gameRunning) {
        while (!move->isMoveComplete()) {
        }

        if (move->isMoveComplete()) {
            std::array<Position, 2> m = move->getMove();
            Piece *self = board_->getBoard()[m[0].getY()][m[0].getX()]->getPiece();
            Piece *enemy = board_->getBoard()[m[1].getY()][m[1].getX()]->getPiece();
            if (self == nullptr) {
                error->setErrorMessage("No Figure chosen");
                continue;
            }
            if (self->getColor() != this->currentPlayer_->getColor()) {
                error->setErrorMessage("The other player has to move");
                continue;
            }
            if (enemy != nullptr && self->getColor() == enemy->getColor()) {
                error->setErrorMessage("Own Figure");
                continue;
            }
            try {
                board_->movePiece(move);
                if (this->isCurrentPlayerInCheckMade()) {
                    board_->undoMove();
                    error->setErrorMessage("Player is in check");
                    std::cout<< "Player is in check"<< std::endl;
                    continue;
                }
                nextPlayer();
                if (isGameOver()) {
                    std::cout << "GAME OVER" << std::endl;
                    error->setErrorMessage("GAME OVER");
                    gameRunning = false;
                }
            }
            catch (std::runtime_error &e) {
                error->setErrorMessage(e.what());
            }
        }
    }
}

bool Game::isCurrentPlayerInCheckMade() {
    King *king;
    if (currentPlayer_->getColor() == Color::WHITE) {
        king = dynamic_cast<King *>(this->board_->getKings()[0]);
    } else {
        king = dynamic_cast<King *>(this->board_->getKings()[1]);
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Move move;
            move.addPosition({j, i});
            if (king != nullptr) {
                move.addPosition(king->getPosition());
                Piece *piece = this->board_->getField({j, i})->getPiece();
                if (piece != nullptr && piece->getColor() != this->currentPlayer_->getColor() &&
                    piece->isMoveValid(&move)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::isGameOver() {
    if (!isCurrentPlayerInCheckMade()) {
        return false;
    }

    for (auto fields: this->board_->getBoard()) {
        for (auto field: fields) {
            Piece *piece = field->getPiece();
            if (piece) {
                if(piece->getColor() != currentPlayer_->getColor()){
                    continue;
                }
                for (int i = 0; i < 8; ++i) {
                    for (int j = 0; j < 8; ++j) {
                        Piece *enemy = board_->getField({j, i})->getPiece();
                        if (enemy != nullptr && enemy->getColor() == piece->getColor()) {
                            continue;
                        }
                        Move move;
                        move.addPosition(piece->getPosition());
                        move.addPosition({j, i});
                        //std::cout << j << " " << i << std::endl;
                        if (piece->isMoveValid(&move)) {
                            this->board_->movePiece(&move);
                            if (!isCurrentPlayerInCheckMade()) {
                                this->board_->undoMove();
                                std::cout << piece->getName() << std::endl;
                                std::cout << j << " " << i << std::endl;
                                return false;
                            }
                            this->board_->undoMove();
                        }
                    }
                }
            }
        }
    }
    // TODO Eventuell jeden Möglichen versuch auf den Board versuchen also 16 * 64 möglichkeiten testen
    return true;
}