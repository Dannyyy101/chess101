#include <iostream>
#include <thread>
#include <array>
#include "../include/gui/Window.h"

int main() {
    Session session;
    Game game;
    Board board = game.getBoard();
    Window window;


    auto *error = &session.error;
    auto *move = &session.move;

    try {
        std::thread gameThread(&Game::runGame, &game, &session);

        window.setUpWindow(board.getBoard());
        window.runWindow(&session, &board);
        
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    delete error;
    delete move;

    return 0;
}
