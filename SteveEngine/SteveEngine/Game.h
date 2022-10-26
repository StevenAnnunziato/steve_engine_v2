#pragma once

#include <vector>

#include "System.h"
#include "Entity.h"

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
    Uint32 frameStart;
    bool quit;
    int frame;
};

struct World
{
    World()
    {
        numTransforms, numRenderers, numColliders, numControllers, numColorChangers = 0;
    }

    static const int MAX_OBJECTS = 128; // TODO: let the user specify this

    // contiguous storage for all components
    Transform transform_array[MAX_OBJECTS];
    RectangleRenderer renderer_array[MAX_OBJECTS];
    RectangleCollider collider_array[MAX_OBJECTS];
    PlayerController controller_array[MAX_OBJECTS];
    ColliderColorChanger colorchanger_array[MAX_OBJECTS];

    // counters for each component
    short int numTransforms;
    short int numRenderers;
    short int numColliders;
    short int numControllers;
    short int numColorChangers;

    // functions to return the next component
    Transform* GetNextTransform() { return &transform_array[numTransforms++]; }
    RectangleRenderer* GetNextRenderer() { return &renderer_array[numRenderers++]; }
    RectangleCollider* GetNextCollider() { return &collider_array[numColliders++]; }
    PlayerController* GetNextController() { return &controller_array[numControllers++]; }
    ColliderColorChanger* GetNextColorChanger() { return &colorchanger_array[numColorChangers++]; }
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
    World theWorld;
};

