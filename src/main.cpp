#include <iostream>
#include <thread>
#include <array>
#include "../include/gui/Window.h"

int main() {
    Game game;
    Board board = game.getBoard();
    Window window;

    auto *error = new Error();
    auto *move = new Move();
    std::atomic<bool> gameRunning(true);

    try {
        std::thread gameThread(&Game::runGame, &game, move, error);

        window.setUpWindow(board.getBoard());
        window.runWindow(move, error, &board);
        
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    delete error;
    delete move;

    return 0;
}
