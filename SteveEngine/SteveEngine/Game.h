#pragma once

#include "System.h"

class Vector2;

struct EngineState
{
    SDL_Renderer* renderer;
    SteveEngine::System* system;
    Uint32 frameStart;
    bool quit;
    int frame;
};

class Game
{

public:
    // constructor / destructor
	Game();
	~Game();

    // setup and cleanup
	void initGame(const Vector2& size);
	void cleanupGame();

    // instance management


    // main loop functions
    void runMainLoop(EngineState* engine);
    void handleTiming(void* engine);

    // updating game state
    void updateGameState(void* arg);
    void renderGame(EngineState* engine);

private:
    static Game* spTheGame;
};

