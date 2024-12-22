// Button.hpp
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const sf :: Vector2f& size, const sf :: Vector2f& position, 
           const sf :: Color& normalColor, const sf :: Color& hoverColor, 
           const sf :: Color& pressedColor, const sf :: Font& font, 
           const std :: string& textString, unsigned int characterSize = 20);

    void draw(sf :: RenderWindow& window);

    void update(const sf :: RenderWindow& window, const sf :: Event& event);

    bool isClicked() const;

private:
    sf :: RectangleShape shape; 
    sf :: Text text;            
    sf :: Color normalColor;    
    sf :: Color hoverColor;     
    sf :: Color pressedColor;   
    bool clicked;             
};

#endif
