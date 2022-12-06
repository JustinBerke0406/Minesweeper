#include "MineTile.h"
#include "Toolbox.h"

void MineTile::onClickLeft()
{
    if (getState() == State::HIDDEN)
    {
        setState(State::EXPLODED);

        Toolbox::getInstance().gameState->setPlayStatus(GameState::LOSS);

        Toolbox::getInstance().hasGameStarted = false;

        Toolbox::getInstance().newGameButton->setSprite(Toolbox::getInstance().images->getSpritePointer("face_lose.png"));
    }
}

void MineTile::draw()
{
    auto& window = Toolbox::getInstance().window;
    auto& gameState = Toolbox::getInstance().gameState;
    ImageHelper* image = Toolbox::getInstance().images;

    if (getState() == State::EXPLODED || gameState->getPlayStatus() == GameState::LOSS) {
        window.draw(image->getSprite("tile_revealed.png", getLocation()));
        window.draw(image->getSprite("mine.png", getLocation()));
    }
    else {
        window.draw(image->getSprite("tile_hidden.png", getLocation()));

        if (Toolbox::getInstance().debugMode)
            window.draw(image->getSprite("mine.png", getLocation()));

        if (getState() == State::FLAGGED)
            window.draw(image->getSprite("flag.png", getLocation()));
    }
}

bool MineTile::isMine()
{
    return true;
}
