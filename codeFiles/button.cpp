// Button.cpp
#include "Button.hpp"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, 
             const sf::Color& normalColor, const sf::Color& hoverColor, 
             const sf::Color& pressedColor, const sf::Font& font, 
             const std::string& textString, unsigned int characterSize)
    : normalColor(normalColor), hoverColor(hoverColor), 
      pressedColor(pressedColor), clicked(false)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(normalColor);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);

    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(characterSize);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.f,
                  textBounds.top + textBounds.height / 2.f);
    text.setPosition(
        position.x + size.x / 2.f,
        position.y + size.y / 2.f
    );
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void Button::update(const sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool isHovering = shape.getGlobalBounds().contains(mousePos);

    if (isHovering) {
        if (event.type == sf::Event::MouseMoved) {
            shape.setFillColor(hoverColor);
        }
    } else {
        shape.setFillColor(normalColor);
    }

    if (isHovering && event.type == sf::Event::MouseButtonPressed && 
        event.mouseButton.button == sf::Mouse::Left) {
        shape.setFillColor(pressedColor);
        clicked = false;
    }

    if (event.type == sf::Event::MouseButtonReleased && 
        event.mouseButton.button == sf::Mouse::Left) {
        clicked = false;
        if (isHovering) {
            clicked = true;
        }

        shape.setFillColor(isHovering ? hoverColor : normalColor);
    }
}

bool Button::isClicked() const {
    return clicked;
}
