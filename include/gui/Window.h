#ifndef WINDOW_H
#define WINDOW_H

#include <array>

#include "../domain/Board.h"
#include "GuiField.h"
#include "../domain/utils/Error.h"
#include "../domain/utils/Move.h"

typedef std::array<std::array<GuiField *, 8>, 8> f_size;

class Window {
private:
    f_size fields_{};
public:
    Window();
    ~Window();
    void setUpWindow(b_size board);
    void updateWindow(b_size board);
    void makeMove(Move * move, std::array<float, 2>& newMove);
    void runWindow(Move * move, Error * error, Board * board);
    void displayError(const std::string& errorMessage);
};

#endif // WINDOW_H