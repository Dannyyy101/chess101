
#include <gtest/gtest.h>
#include "../include/domain/Board.h"
#include "../include/domain/pieces/Pawn.h"

TEST(PieceMoveTest, PawnMovesCorrect) {
    Board board(false);
    board.getField({4, 4})->setPiece(new Pawn("pawn", Color::WHITE, {4, 4}, &board));
    Piece * pawn = board.getField({4, 4})->getPiece();
    board.getField({5, 3})->setPiece(new Pawn("pawn", Color::WHITE, {5, 3}, &board));
    Piece * enemy = board.getField({5, 3})->getPiece();
    Move move1;
    move1.addPosition({4, 4});
    move1.addPosition({4, 3});
    EXPECT_TRUE(pawn->isMoveValid(&move1));
    Move move2;
    move2.addPosition({4, 4});
    move2.addPosition({4, 2});
    EXPECT_TRUE(pawn->isMoveValid(&move2));
    Move move3;
    move3.addPosition({4, 4});
    move3.addPosition({5, 3});
    EXPECT_TRUE(pawn->isMoveValid(&move3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
