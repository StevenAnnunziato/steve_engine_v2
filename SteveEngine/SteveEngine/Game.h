#pragma once

#include <vector>

#include "System.h"
#include "Entity.h"

class Vector2;
class Vector3;
class Color;

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

    // instance management for Game singleton
    static Game* getInstance() { return spTheGame; }
    static void initInstance();
    static void cleanupInstance();

    // setup and cleanup
	void initGame(const Vector2& size);
	void cleanupGame();

    // main loop functions
    void runMainLoop(EngineState* engine);
    void handleTiming(void* engine);

    // updating game state
    void updateGameState(void* arg);
    void renderGame(EngineState* engine);

private:
    static Game* spTheGame;
    std::vector<Entity*> gameEntities;
};

