//
// Created by Daniel Stöcklein on 02.08.24.
//

#include "../../../include/domain/pieces/King.h"
#include "../../../include/domain/pieces/Rook.h"
#include "../../../include/domain/pieces/Bishop.h"

King::King(std::string name, Color color, Position position, Board *board) : Piece(name, color, position, board) {}

King::~King() = default;

bool King::isMoveValid(Move *move) {
    Position self = this->getPosition();
    Position position = move->getMove()[1];
    Board * board = this->getBoard();
    Rook rook("king", getColor(), self, board);
    Bishop bishop("king", getColor(), self, board);

    // Rochade
    // TODO Kann sein das wenn es hier oben steht ungültige Züge möglich sind
    Piece * piece = board->getField(position)->getPiece();


    if(!this->hasMoved && piece && dynamic_cast<Rook *>(piece)){
        int direction = position.getX() > self.getX() ? 1 : -1;
        for (int i = 1; i < std::abs(position.getX() - self.getX()); ++i) {
            if(board_->getField({self.getX() + (i * direction), self.getY()})->getPiece()){
                std::cout << board_->getField({self.getX() + (i * direction), self.getY()})->getPiece()->getName() << "\n";
                return false;
            }
        }
        return true;
    }

    if(rook.isMoveValid(move)){
        if(std::abs(self.getX() - position.getX()) + std::abs(self.getY() - position.getY()) == 1){
            return true;
        }else{
            return false;
        }
    }
    if(bishop.isMoveValid(move)){
        if(std::abs(self.getX() - position.getX()) + std::abs(self.getY() - position.getY()) == 2){
            return true;
        }else{
            return false;
        }
    }


    return false;
}

