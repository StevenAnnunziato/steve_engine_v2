#include <iostream>

#include "Game.h"
#include "Utils.h"
#include "LevelParser.h"

#include "PlayerController.h"
#include "ColliderColorChanger.h"
#include "RectangleRenderer.h"

Game* Game::spTheGame = nullptr;

Game::Game()
{
}

Game::~Game()
{
}

// TODO: Reformat to put RunMainLoop and cleanup fns in another place!
void Game::initGame(const Vector2& windowSize)
{
    // init system
    SteveEngine::System system;
    system.Init();

    // create and init renderer
    theRenderer = Renderer();
    theRenderer.init(windowSize);

    // init stack allocator
    int bufferSize = 1024 * 10; // 10 kb
    StackAllocator stackAllocator(bufferSize);

    // init engine state
    EngineState engine;
    engine.quit = false;
    engine.stackAllocator = &stackAllocator;
    engine.frame = 0;
    engine.frameStart = SDL_GetTicks();
    engine.system = &system;

    // create game world
    theWorld = World();

    // create game entities by parsing through a text file
    LevelParser parser;
    parser.LoadLevel(&engine);

    // game is here
    runMainLoop(&engine);

    // cleanup
    cleanupGame();
    theRenderer.cleanup();

    // quit game
    SDL_Quit();

    system.Shutdown();
}

void Game::cleanupGame()
{
    // delete all game entities
    for (int i = 0; i < gameEntities.size(); i++)
    {
        delete gameEntities[i];
        gameEntities[i] = nullptr;
    }
}

// instance management
void Game::initInstance()
{
    if (spTheGame == nullptr)
        spTheGame = DBG_NEW Game();
}
void Game::cleanupInstance()
{
    delete spTheGame;
}

// runMainLoop:
// Starts the main loop with different parameters depending on platform.
// Note: This could be combined with handleTiming, but it is separated
//       to allow for multiplatform builds with Emscripten.
void Game::runMainLoop(EngineState* engine)
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(handleTiming, engine, 0, true);
#else

    while (!engine->quit)
    {
        handleTiming(engine);
    }
#endif
}

// handleTiming:
// Does input resolution, physics calculations and 
void Game::handleTiming(void* engine)
{
    Uint32 now = SDL_GetTicks();
    if (now - ((EngineState*)engine)->frameStart >= 16)
    {
        updateGameState((EngineState*)engine);
        theRenderer.renderGame();

        // clear stack allocator
        ((EngineState*)engine)->stackAllocator->clear();
    }
}

// physics, input, etc
void Game::updateGameState(void* arg)
{
    EngineState* engine = (EngineState*)arg;
    SDL_Event event;

    // TODO: move this block to timing
    Uint32 now = SDL_GetTicks();
    engine->frame++;
    engine->frameStart = now;
    // --------------------------------

    // update physics
    updatePhysics(engine);

    // update all components
    // Note: only player controllers and collider color changers have update functions right now.
    for (int i = 0; i < getWorld()->numControllers; i++)
    {
        getWorld()->controller_array[i].Update();
    }
    for (int i = 0; i < getWorld()->numControllers; i++)
    {
        getWorld()->colorchanger_array[i].Update(gameEntities);
    }

    // input for basic game functionality
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            engine->quit = true;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_k)
            {
                std::cout << "K pressed!\n";

                engine->system->ShowError(ERROR_K);
                engine->system->LogToErrorFile(ERROR_K);

            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                engine->quit = true;
            }
        }
    }
}

void Game::updatePhysics(EngineState* engine)
{
    RectangleCollider** colliderArray = (RectangleCollider**)engine->stackAllocator->getHeadAddress(); // array of RectangleCollider pointers
    // get an array of all colliders that are colliding with anything else
    // NOTE: this might add objects several times, but this is just an example for now
    int size = 0;
    for (int i = 0; i < getWorld()->numColliders; i++)
    {
        for (int j = 0; j < getWorld()->numColliders; j++)
        {
            // don't collide with myself
            if (&getWorld()->collider_array[i] == &getWorld()->collider_array[j])
                continue;

            // are i and j colliding?
            if (getWorld()->collider_array[i].CheckCollision(&getWorld()->collider_array[j]))
            {
                // colliding - allocate space on the stack allocator
                colliderArray[size] = *engine->stackAllocator->alloc<RectangleCollider*>();
                colliderArray[size] = &getWorld()->collider_array[i];
                size++;
            }
        }
    }
    
    // show text with frame number
    int bufferSize = 13;  // 13 chars should be enough for "frame: xxxxxx"
    char* frameStr = engine->stackAllocator->alloc<char>(bufferSize);
    snprintf(frameStr, bufferSize, "Frame: %d", engine->frame);
    //puts(frameStr);

    // display collider array!
    /*for (int i = 0; i < size; i++)
    {
        std::cout << colliderArray[i]->GetOwner()->GetTransform()->position.x << std::endl;
    }*/
}

Entity* Game::createNewEntity()
{
    Entity* ent = DBG_NEW Entity();
    gameEntities.push_back(ent);
    return ent;
}
