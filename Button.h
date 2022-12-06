#pragma once

#include <utility>
#include <SFML/Graphics.hpp>

class Button
{
private:
    sf::Vector2f position;
    std::function<void(void)> func;
    sf::Sprite* sprite = nullptr;
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick): position(_position), func(std::move(_onClick)) {};

    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
    void draw();
};