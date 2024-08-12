#ifndef GUI_FIELD
#define GUI_FIELD

#include "../../include/domain/utils/Color.h"
#include <SFML/Graphics.hpp>
#include "../gui/Window.h"

class GuiField {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string imageUrl;
    sf::Color color_;
public:
    sf::RectangleShape rect;

    GuiField(float x, float y, int width, int height, int color);

    ~GuiField();

    void draw(sf::RenderWindow &window);

    void changeImage(const std::string &url);

    bool isPressed(sf::RenderWindow &window);

    sf::RectangleShape& getShape() ;

    std::string getImageUrl();

    void removeImage();

    void unFocus();
};

#endif
