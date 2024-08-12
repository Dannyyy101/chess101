#ifndef WINDOW_H
#define WINDOW_H

#define FIELD_SIZE 100.0
#define WINDOW_SIZE 800
#define IMAGE_PATH "resources/pieces/"

#include <array>

#include "../domain/Board.h"
#include "GuiField.h"
#include "../Session.h"

class GuiField;
typedef std::array<std::array<GuiField *, 8>, 8> f_size;

class Window {
private:
    f_size fields_{};
public:
    Window();
    ~Window();
    void setUpWindow(b_size board);
    void updateWindow(b_size board);
    void makeMove(Session * session, std::array<float, 2>& newMove);
    void runWindow(Session * session, Board * board);
    void displayError(const std::string& errorMessage);
};

#endif // WINDOW_H