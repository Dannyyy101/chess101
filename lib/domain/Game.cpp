//
// Created by Daniel Stöcklein on 02.08.24.
//

#include "../../include/domain/Game.h"
#include "../../include/domain/Player.h"
#include "../../include/domain/pieces/King.h"
#include "../../include/domain/pieces/Pawn.h"
#include "../../include/domain/pieces/Queen.h"
#include "../../include/domain/pieces/Rook.h"
#include "../../include/domain/pieces/Knight.h"
#include "../../include/domain/pieces/Bishop.h"
#include <iostream>

Game::Game() : board_(new Board()), stalemateCounter(0) {
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

void Game::runGame(Session *session) {
    Move *move = &session->move;
    Error *error = &session->error;
    bool gameRunning = true;

    while (gameRunning) {

        // check piece selection for pawn evolution
        if (session->hasPawnBeenChanged()) {
            changePawn(session);
        }

        if (move->isMoveComplete()) {
            try {
                std::array<Position, 2> m = move->getMove();
                Piece *piece = board_->getBoard()[m[0].getY()][m[0].getX()]->getPiece();
                Piece *enemy = board_->getBoard()[m[1].getY()][m[1].getX()]->getPiece();

                if (piece == nullptr) {
                    throw std::runtime_error("No Figure chosen");
                }
                if (piece->getColor() != this->currentPlayer_->getColor()) {
                    throw std::runtime_error("The other player has to move");
                }
                bool moveIsRochade = rochade(move);
                if (enemy != nullptr && piece->getColor() == enemy->getColor() && !moveIsRochade) {
                    throw std::runtime_error("Own Figure");
                }

                if (piece->isMoveValid(move)) {
                    if (m[0] == m[1]) {
                        throw std::runtime_error("same Position");
                    }
                    bool valid = true;
                    board_->movePiece(move);
                    if (this->isCurrentPlayerInCheckMade()) {
                        board_->undoMove();
                        error->setErrorMessage("Player is in check");
                        valid = false;
                    }

                    // pawn evolve when on the other site of the board
                    if (valid && dynamic_cast<Pawn *>(piece) && (m[1].getY() == 0 || m[1].getY() == 7)) {
                        session->setNeedsPawnToEvolve(true);
                        session->setPositionFromPawnToEvolve(m[1]);
                    }

                    // rochade
                    if (valid && moveIsRochade && enemy) {
                        int x = piece->getPosition().getX();
                        int y = piece->getPosition().getY();

                        piece->setPosition({x == 0 ? 1 : 6, y});
                        board_->getField({x, y})->setPiece(nullptr);
                        board_->getField({x = (x == 0 ? 1 : 6), y})->setPiece(piece);

                        board_->getField({x != 1 ? 5 : 2, y})->setPiece(enemy);
                        enemy->setPosition({x != 1 ? 5 : 2, y});


                        this->board_->getFieldWithNames();
                    }
                    Move *lastMove = currentPlayer_->getLastMove();
                    this->currentPlayer_->addMove(move);
                    if (valid && lastMove != nullptr) {
                        if (*lastMove == *move) {
                            stalemateCounter++;
                        } else {
                            stalemateCounter = 0;
                        }
                        if (stalemateCounter == 6) {
                            error->setErrorMessage("GAME OVER");
                            gameRunning = false;
                        }
                    }
                } else {
                    throw std::runtime_error("Bad move");
                }

                nextPlayer();
                if (isGameOver()) {
                    std::cout << "GAME OVER" << std::endl;
                    error->setErrorMessage("GAME OVER");
                    gameRunning = false;
                }
            }
            catch (std::runtime_error &e) {
                std::cerr << e.what() << "\n";
                move->setMoveComplete(false);
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
                if (piece->getColor() != currentPlayer_->getColor()) {
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

void Game::changePawn(Session *session) {
    int index = session->getPieceToChangeTo();
    Position position = {session->getPositionFromPawnToEvolve()[0], session->getPositionFromPawnToEvolve()[1]};
    Piece *oldPiece = board_->getBoard()[position.getY()][position.getX()]->getPiece();
    Piece *piece;
    switch (index) {
        case 0:
            piece = new Queen("queen", oldPiece->getColor(), oldPiece->getPosition(), board_);
            break;
        case 1:
            piece = new Knight("knight", oldPiece->getColor(), oldPiece->getPosition(), board_);
            break;
        case 2:
            piece = new Rook("rook", oldPiece->getColor(), oldPiece->getPosition(), board_);
            break;
        case 3:
            piece = new Bishop("bishop", oldPiece->getColor(), oldPiece->getPosition(), board_);
            break;
        default:
            throw std::runtime_error("Can change to selected Piece");
    }
    std::cout << session->getPieceToChangeTo() << "\n";
    board_->getBoard()[position.getY()][position.getX()]->setPiece(piece);
    delete oldPiece;
    session->setNeedsPawnToEvolve(false);
}

bool Game::rochade(Move *move) {

    Position self = move->getMove()[0];
    Position position = move->getMove()[1];
    Piece *king = board_->getField(self)->getPiece();
    Piece *piece = board_->getField(position)->getPiece();

    if (king && piece && dynamic_cast<King *>(king) && dynamic_cast<Rook *>(piece)) {
        if (!king->getHasMoved()) {
            int direction = position.getX() > self.getX() ? 1 : -1;
            for (int i = 1; i < std::abs(position.getX() - self.getX()); ++i) {
                if (board_->getField({self.getX() + (i * direction), self.getY()})->getPiece()) {
                    std::cout << board_->getField({self.getX() + (i * direction), self.getY()})->getPiece()->getName()
                              << "\n";
                    return false;
                }
            }
        }
    } else {
        return false;
    }
    return true;
}