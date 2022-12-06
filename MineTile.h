#pragma once

#include "Tile.h"

class MineTile : public Tile
{
private:
    bool isMine() override; // Return is this is a mine
public:
    explicit MineTile(sf::Vector2f position): Tile(position) {};

    void onClickLeft() override;
    void draw() override;
};