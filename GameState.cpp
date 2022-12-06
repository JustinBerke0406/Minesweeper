#include "GameState.h"
#include "MineTile.h"

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines)
{
    dimensions = _dimensions;
    numberOfMines = _numberOfMines;

    status = PlayStatus::PLAYING;

    fillBoard();

    determineNeighbors();
}

GameState::~GameState()
{
    for (int i = 0; i < dimensions.x * dimensions.y; i++)
        delete tiles[i];
}

int GameState::getFlagCount()
{
    int count = 0;

    for (int i = 0; i < dimensions.x * dimensions.y; i++)
        if (tiles[i]->getState() == Tile::State::FLAGGED) count++;

    return count;
}

int GameState::getMineCount()
{
    return numberOfMines;
}

Tile *GameState::getTile(int x, int y)
{
    if (x >= 0 and x < dimensions.x and y >= 0 and y < dimensions.y)
        return tiles[x + y * dimensions.x];

    return nullptr;
}

GameState::PlayStatus GameState::getPlayStatus()
{
    return status;
}

void GameState::setPlayStatus(GameState::PlayStatus _status)
{
    status =_status;
}

void GameState::fillBoard()
{
    int minesOnBoard = 0, size = dimensions.x*dimensions.y;

    // Initialize array with null pointers
    for (int i = 0; i < size; i++)
        tiles.push_back(nullptr);

    std::vector<int> mineLocations;

    // Random generator
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_int_distribution<int> range(0, size);

    while (minesOnBoard < numberOfMines) {
        int randNum = range(mt);

        // If location already has a MineTile, skip this loop iteration
        if (std::find(mineLocations.begin(), mineLocations.end(), randNum) != mineLocations.end())
            continue;

        // Insert MineTile at the given random location
        tiles[randNum] = new MineTile(sf::Vector2f((randNum % dimensions.x) * WINDOW_WIDTH / dimensions.x,
                (randNum / dimensions.x) * (WINDOW_HEIGHT * BOTTOM_MARGIN) / dimensions.y));

        // Store where the MineTile is
        mineLocations.push_back(randNum);

        // Count the current number of mines on the board
        minesOnBoard++;
    }

    // Fill the rest of the board with Tiles
    for (int i = 0; i < size; i++)
        if (tiles[i] == nullptr)
            tiles[i] = new Tile(sf::Vector2f((i % dimensions.x) * WINDOW_WIDTH / dimensions.x,
                    (i / dimensions.x) * (WINDOW_HEIGHT * BOTTOM_MARGIN) / dimensions.y));
}

sf::Vector2i GameState::getDimensions()
{
    return dimensions;
}

GameState::GameState(const char *filepath)
{
    int mineCount = 0;
    int bufferResist;

    std::ifstream read(filepath);

    std::string data;
    std::vector<std::string> allData;

    // Store all file data in a vector of strings
    while (read)
    {
        read >> data;
        allData.push_back(data);

        // Count number of mines in the incoming line of data
        bufferResist = std::count(data.begin(), data.end(), '1');
        mineCount += bufferResist;
    }

    // Subtract the number of mines in the last row as the last row is read twice due to how the file is being read
    mineCount -= bufferResist;

    dimensions = sf::Vector2i(allData[0].size(), allData.size()-1);
    numberOfMines = mineCount;
    status = PlayStatus::PLAYING;

    // Insert a Tile or MineTile dependent if the file shows a 0 or 1 at that location
    for (int y = 0; y < dimensions.y; y++)
        for (int x = 0; x < dimensions.x; x++) {
            if (allData[y][x] == '0')
                tiles.push_back(new Tile(sf::Vector2f(x * WINDOW_WIDTH / dimensions.x, y * (WINDOW_HEIGHT * BOTTOM_MARGIN) / dimensions.y)));
            else
                tiles.push_back(new MineTile(sf::Vector2f(x * WINDOW_WIDTH / dimensions.x, y * (WINDOW_HEIGHT * BOTTOM_MARGIN) / dimensions.y)));
        }

    determineNeighbors();
}

void GameState::determineNeighbors()
{
    int index, neighborIndex, adjacentIndex;

    for (int _y = 0; _y < dimensions.y; _y++)
        for (int _x = 0; _x < dimensions.x; _x++) {
            index = _x + _y * dimensions.x;

            // Get tile and initialize neighbors to null pointers
            Tile* tile = tiles[index];
            tile->setNeighbors({nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr});

            neighborIndex = 0;

            for (int y = _y - 1; y < _y + 2; y++)
                for (int x = _x - 1; x < _x + 2; x++) {
                    // Continue if the neighbor location is equal to the current Tile's position
                    if (y == _y and x == _x) continue;

                    // Sets the neighbor at a location if the location is valid
                    if (x >= 0 and x < dimensions.x and y >= 0 and y < dimensions.y) {
                        adjacentIndex = x + y * dimensions.x;

                        tile->getNeighbors()[neighborIndex] = tiles[adjacentIndex];

                        // If the inputted neighbor came before the current tile, add the current tile to the
                        // neighbor's neighbor list
                        if (adjacentIndex < index)
                        {
                            auto adjNeighbors = tiles[adjacentIndex]->getNeighbors();
                            adjNeighbors[7 - neighborIndex] = tile;
                        }
                    }

                    neighborIndex++;
                }
        }
}
