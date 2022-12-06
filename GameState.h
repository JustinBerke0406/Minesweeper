#pragma once

#include "Tile.h"
#include <random>
#include <fstream>
#include "Constants.h"

using namespace Constants;

class GameState
{
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
private:
    sf::Vector2i dimensions;
    int numberOfMines;
    PlayStatus status;
    std::vector<Tile*> tiles;

    void fillBoard();           // Fills the board with a mix of Tiles and MineTiles
    void determineNeighbors();  // Sets the neighbors of each Tile
public:
    explicit GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    explicit GameState(const char* filepath);

    int getFlagCount(); // Flags on board
    int getMineCount(); // Mines in board
    sf::Vector2i getDimensions();   // Board dimensions
    Tile* getTile(int x, int y);    // Gets Tile at (x, y)
    PlayStatus getPlayStatus();     // Gets play status
    void setPlayStatus(PlayStatus _status); // Sets play status

    ~GameState();   // Destructor
};
