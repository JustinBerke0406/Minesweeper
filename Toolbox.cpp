#include "Toolbox.h"
#include "minesweeper.h"

Toolbox::Toolbox()
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "P4 - Minesweeper, Justin Berke");

    debugMode = false;
    hasGameStarted = false;
    stoppedTime = 0;

    gameState = new GameState();
    images = new ImageHelper();

    // Create new game button and define its behavior
    newGameButton = new Button(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT*BOTTOM_MARGIN), [] () {
        restart();
    });

    newGameButton->setSprite(images->getSpritePointer("face_happy.png"));

    // Create debug button and define its behavior
    debugButton = new Button(sf::Vector2f(2*WINDOW_WIDTH/3, WINDOW_HEIGHT*BOTTOM_MARGIN), [] () {
        toggleDebugMode();
    });

    debugButton->setSprite(images->getSpritePointer("debug.png"));

    // Create test button 1 and define its behavior
    testButton1 = new Button(sf::Vector2f(3*WINDOW_WIDTH/4, WINDOW_HEIGHT*BOTTOM_MARGIN), [this] () {
        delete gameState;

        debugMode = false;
        hasGameStarted = false;
        stoppedTime = 0;

        newGameButton->setSprite(images->getSpritePointer("face_happy.png"));

        gameState = new GameState("boards/testboard1.brd");
    });

    testButton1->setSprite(images->getSpritePointer("test_1.png"));

    // Create test button 2 and define its behavior
    testButton2 = new Button(sf::Vector2f(5*WINDOW_WIDTH/6, WINDOW_HEIGHT*BOTTOM_MARGIN), [this] () {
        delete gameState;

        debugMode = false;
        hasGameStarted = false;
        stoppedTime = 0;

        newGameButton->setSprite(images->getSpritePointer("face_happy.png"));

        gameState = new GameState("boards/testboard2.brd");
    });

    testButton2->setSprite(images->getSpritePointer("test_2.png"));
}

Toolbox::~Toolbox()
{
    delete gameState;
    delete newGameButton;
    delete debugButton;
    delete testButton1;
    delete testButton2;
}

std::array<Button*, 4> Toolbox::buttonList()
{
    return {newGameButton, debugButton, testButton1, testButton2};
}
