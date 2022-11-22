#pragma once

#include <vector>

#include "System.h"
#include "Entity.h"
#include "StackAllocator.h"

#include "Transform.h"
#include "RectangleRenderer.h"
#include "RectangleCollider.h"
#include "PlayerController.h"
#include "ColliderColorChanger.h"

class Vector2;
class Vector3;
class Color;

struct EngineState
{
    SDL_Renderer* renderer;
    SteveEngine::System* system;
    StackAllocator* stackAllocator;
    Uint32 frameStart;
    bool quit;
    int frame;
};

struct World
{
    World()
    {
        numRenderers = 0;
        numColliders = 0;
        numControllers = 0;
        numColorChangers = 0;
    }

    static const int MAX_OBJECTS = 128; // TODO: let the user specify this

    // contiguous storage for all components
    RectangleRenderer renderer_array[MAX_OBJECTS];
    RectangleCollider collider_array[MAX_OBJECTS];
    PlayerController controller_array[MAX_OBJECTS];
    ColliderColorChanger colorchanger_array[MAX_OBJECTS];

    // counters for each component
    int numRenderers;
    int numColliders;
    int numControllers;
    int numColorChangers;

    // functions to return the next component
    RectangleRenderer* GetNextRenderer() 
    { 
        if (numRenderers >= MAX_OBJECTS)
            return nullptr;
        return &renderer_array[numRenderers++]; 
    }
    RectangleCollider* GetNextCollider()
    {
        if (numColliders >= MAX_OBJECTS)
            return nullptr;
        return &collider_array[numColliders++];
    }
    PlayerController* GetNextController()
    {
        if (numControllers >= MAX_OBJECTS)
            return nullptr;
        return &controller_array[numControllers++];
    }
    ColliderColorChanger* GetNextColorChanger() 
    { 
        if (numColorChangers >= MAX_OBJECTS)
            return nullptr;
        return &colorchanger_array[numColorChangers++]; 
    }
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
    World* getWorld() { return &theWorld; }

    // setup and cleanup
	void initGame(const Vector2& size);
	void cleanupGame();

    // main loop functions
    void runMainLoop(EngineState* engine);
    void handleTiming(void* engine);

    // updating game state
    void updateGameState(void* arg);
    void updatePhysics(EngineState* engine);
    void renderGame(EngineState* engine);

    // additional helper functions
    Entity* createNewEntity();

private:
    static Game* spTheGame;
    std::vector<Entity*> gameEntities;
    World theWorld;
};

