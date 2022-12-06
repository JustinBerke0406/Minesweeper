#include <iostream>
#include "minesweeper.h"

int launch() {
    Toolbox& toolbox = Toolbox::getInstance();

    sf::RenderWindow& window = toolbox.window;

    sf::Vector2i dimensions = toolbox.gameState->getDimensions();

    // Event needed for window to work
    sf::Event event{};

    // For loop to keep window open
    while (window.isOpen())
    {
        // Draw spriteHidden
        window.clear(sf::Color(255,255,255));

        // Render game
        render();

        // draw method
        window.display();

        if (window.pollEvent(event)) {
            // Close window event
            if (event.type == sf::Event::Closed)
                window.close();
            // Mouse clicked event
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                // Get clicked tile
                Tile *tile = toolbox.gameState->getTile(dimensions.x * x / window.getSize().x, dimensions.y * y / (window.getSize().y*BOTTOM_MARGIN));

                if (toolbox.gameState->getPlayStatus() == GameState::PLAYING && tile != nullptr)
                {
                    if (event.mouseButton.button == sf::Mouse::Right)
                        tile->onClickRight();
                    else if (event.mouseButton.button == sf::Mouse::Left)
                        tile->onClickLeft();
                }
                else // If tile not clicked
                {
                    auto buttonList = toolbox.buttonList();

                    // Get window coordinates
                    sf::Vector2f coords = window.mapPixelToCoords(sf::Vector2i(x, y));

                    // Check bounds of every button
                    for (Button *button: buttonList)
                        if (button != nullptr and button->getSprite()->getGlobalBounds().contains(coords))
                            button->onClick();
                }
            }
        }
    }

    return 0;
}

void render() {
    Toolbox& toolbox = Toolbox::getInstance();

    GameState* state = toolbox.gameState;
    sf::RenderWindow& window = toolbox.window;
    ImageHelper* images = toolbox.images;

    sf::Vector2i dimensions = state->getDimensions();

    auto buttonList = toolbox.buttonList();

    // Draw buttons
    for (Button *button : buttonList)
        if (button != nullptr)
            button->draw();

    // Draw each tile
    for (int x = 0; x < dimensions.x; x++)
        for (int y = 0; y < dimensions.y; y++)
            state->getTile(x, y)->draw();


    int flags = state->getMineCount() - state->getFlagCount();
    int firstSpriteIndex = flags / 100;

    if (flags < 0) {
        flags *= -1;
        firstSpriteIndex = 10;
    }

    // Draw flags remaining
    window.draw(images->getSprite("digits.png", sf::Vector2f(0, WINDOW_HEIGHT*BOTTOM_MARGIN), 21 * firstSpriteIndex, 21 * (1 + firstSpriteIndex)));
    window.draw(images->getSprite("digits.png", sf::Vector2f(21, WINDOW_HEIGHT*BOTTOM_MARGIN), 21 * ((flags / 10) % 10), 21 * (1 + ((flags / 10) % 10))));
    window.draw(images->getSprite("digits.png", sf::Vector2f(42, WINDOW_HEIGHT*BOTTOM_MARGIN), 21 * (flags % 10), 21 * (1 + (flags % 10))));


    int time = toolbox.clock.getElapsedTime().asSeconds();

    if (!toolbox.hasGameStarted)
        time = toolbox.stoppedTime;
    else
        toolbox.stoppedTime = time;

    if (time > 999)
        time = 999;

    // Draw timer
    window.draw(images->getSprite("digits.png", sf::Vector2f(WINDOW_WIDTH-63, WINDOW_HEIGHT*BOTTOM_MARGIN), 21 * (time / 100), 21 * (1 + (time / 100))));
    window.draw(images->getSprite("digits.png", sf::Vector2f(WINDOW_WIDTH-42, WINDOW_HEIGHT*BOTTOM_MARGIN), 21 * ((time / 10) % 10), 21 * (1 + ((time / 10) % 10))));
    window.draw(images->getSprite("digits.png", sf::Vector2f(WINDOW_WIDTH-21, WINDOW_HEIGHT*BOTTOM_MARGIN), 21 * (time % 10), 21 * (1 + (time % 10))));
}

void restart() {
    Toolbox& toolbox = Toolbox::getInstance();

    delete toolbox.gameState;

    toolbox.gameState = new GameState();

    toolbox.newGameButton->setSprite(toolbox.images->getSpritePointer("face_happy.png"));

    toolbox.debugMode = false;

    toolbox.hasGameStarted = false;

    toolbox.stoppedTime = 0;
}

void toggleDebugMode() {
    Toolbox::getInstance().debugMode = !Toolbox::getInstance().debugMode;
}

bool getDebugMode() {
    return Toolbox::getInstance().debugMode;
}

int main() { return launch(); }