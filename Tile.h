#pragma once

#include "ImageHelper.h"

class Tile
{
public:
    enum State {REVEALED, HIDDEN, FLAGGED, EXPLODED};
private:
    State state;
    sf::Vector2f location;
    std::array<Tile*, 8> neighbors;

    Tile() = default;

    int getSurroundingMines();  // Get number of mines surrounding this tile
    void checkIfWin();          // Check if the game has been won

    virtual bool isMine();      // Is this tile a mine

    void revealNeighbors();     // Reveal neighbors if conditions are correct

    friend class MineTile;
public:
    Tile(sf::Vector2f position): location(position), state(State::HIDDEN) {};

    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);

    virtual void onClickLeft();
    void onClickRight();

    virtual void draw();
};
