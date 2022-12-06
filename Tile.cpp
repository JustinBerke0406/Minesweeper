#include "Tile.h"
#include "Toolbox.h"

sf::Vector2f Tile::getLocation()
{
    return location;
}

Tile::State Tile::getState()
{
    return state;
}

std::array<Tile *, 8> &Tile::getNeighbors()
{
    return neighbors;
}

void Tile::setState(Tile::State _state)
{
    state = _state;
}

void Tile::setNeighbors(std::array<Tile *, 8> _neighbors)
{
    neighbors = _neighbors;
}

void Tile::onClickLeft()
{
    // Start clock
    if (!Toolbox::getInstance().hasGameStarted)
        Toolbox::getInstance().clock.restart();

    Toolbox::getInstance().hasGameStarted = true;

    // Reveal tile and neighbors
    if (state == State::HIDDEN) {
        state = State::REVEALED;

        if (getSurroundingMines() == 0)
            revealNeighbors();

        checkIfWin();
    }
}

void Tile::onClickRight()
{
    if (state == State::FLAGGED) state = State::HIDDEN;
    else if (state == State::HIDDEN) state = State::FLAGGED;
}

void Tile::draw()
{
    auto& window = Toolbox::getInstance().window;
    ImageHelper* image = Toolbox::getInstance().images;

    if (state == State::REVEALED) {
        int mines = getSurroundingMines();

        window.draw(image->getSprite("tile_revealed.png", location));

        // Draw number of surrounding mines if any
        if (mines != 0)
            window.draw(image->getSprite("number_" + std::to_string(mines) + ".png", location));
    }
    else {
        window.draw(image->getSprite("tile_hidden.png", location));

        if (state == State::FLAGGED)
            window.draw(image->getSprite("flag.png", location));
    }
}

void Tile::revealNeighbors()
{
    for (Tile* tile : neighbors) {
        if (tile != nullptr and tile->getState() != State::REVEALED)
        {
            tile->state = State::REVEALED;

            // Reveal neighbors of neighbors if possible
            if (tile->getSurroundingMines() == 0)
                tile->revealNeighbors();
        }
    }
}

int Tile::getSurroundingMines()
{
    int count = 0;

    // Count number of neighbors that are mines
    for (Tile* tile : neighbors)
        count += tile != nullptr and tile->isMine();

    return count;
}

bool Tile::isMine()
{
    return false;
}

void Tile::checkIfWin()
{
    GameState* gameState = Toolbox::getInstance().gameState;
    int revealCount = 0;

    std::vector<Tile*> hidden;

    // Count number of tiles that have been revealed
    for (int y = 0; y < gameState->getDimensions().y; y++)
        for (int x = 0; x < gameState->getDimensions().x; x++)
            if (gameState->getTile(x, y)->getState() == Tile::State::REVEALED)
                revealCount++;
            else
                hidden.push_back(gameState->getTile(x, y));

    // Win if number of remaining hidden tiles equals the number of mines
    if (revealCount == gameState->getDimensions().y*gameState->getDimensions().x - gameState->getMineCount())
    {
        gameState->setPlayStatus(GameState::WIN);

        // Flag all hidden tiles
        for (Tile *tile: hidden)
            tile->setState(Tile::State::FLAGGED);

        Toolbox::getInstance().newGameButton->setSprite(Toolbox::getInstance().images->getSpritePointer("face_win.png"));

        Toolbox::getInstance().hasGameStarted = false;
    }
}
