#pragma once

#include "Button.h"
#include "GameState.h"
#include "Constants.h"

using namespace Constants;

class Toolbox
{

private:
    Toolbox();
public:
    static Toolbox& getInstance() {
        static Toolbox instance;
        return instance;
    }

    sf::RenderWindow window; // SFML application window
    GameState* gameState;    // Primary game state representation
    Button* newGameButton;   // Starts a new game
    Button* debugButton;     // Reveals mines in debug mode
    Button* testButton1;     // Loads test board #1
    Button* testButton2;     // Loads test board #2
    ImageHelper* images;     // Sprite and Texture worker
    sf::Clock clock;         // Handles time

    int stoppedTime;         // Saved time when paused

    bool debugMode;          // Status of debug mode
    bool hasGameStarted;     // Checks if the player clicked on a tile yet

    std::array<Button*, 4> buttonList();  // Returns list of buttons

    ~Toolbox();
};