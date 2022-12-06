#include "Button.h"
#include "Toolbox.h"

sf::Vector2f Button::getPosition()
{
    return position;
}

sf::Sprite *Button::getSprite()
{
    return sprite;
}

void Button::setSprite(sf::Sprite *_sprite)
{
    delete sprite;

    sprite = _sprite;

    sf::Vector2f shift(position.x - sprite->getLocalBounds().width/2, position.y);

    sprite->setPosition(shift);
}

void Button::onClick()
{
    func();
}

void Button::draw()
{
    Toolbox::getInstance().window.draw(*sprite);
}
