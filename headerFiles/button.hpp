// Button.hpp
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    // Constructor
    Button(const sf::Vector2f& size, const sf::Vector2f& position, 
           const sf::Color& normalColor, const sf::Color& hoverColor, 
           const sf::Color& pressedColor, const sf::Font& font, 
           const std::string& textString, unsigned int characterSize = 20);

    // Draw the button on the window
    void draw(sf::RenderWindow& window);

    // Update the button state based on mouse position and events
    void update(const sf::RenderWindow& window, const sf::Event& event);

    // Check if the button was clicked
    bool isClicked() const;

private:
    sf::RectangleShape shape; // Button background
    sf::Text text;            // Button label
    sf::Color normalColor;    // Default color
    sf::Color hoverColor;     // Color on hover
    sf::Color pressedColor;   // Color when pressed
    bool clicked;             // Click state flag
};

#endif // BUTTON_HPP
