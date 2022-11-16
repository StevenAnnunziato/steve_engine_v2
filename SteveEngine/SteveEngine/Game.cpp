#include <iostream>

#include "Game.h"
#include "Utils.h"

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
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SteveEngine::System system;
    system.Init();

    //int* leak = DBG_NEW int[4096]; // this gets caught and displayed in the VS debug output

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.x, windowSize.y, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int bufferSize = 1024 * 10; // 10 kb
    StackAllocator stackAllocator(bufferSize);

    EngineState engine;
    engine.quit = false;
    engine.renderer = renderer;
    engine.stackAllocator = &stackAllocator;
    engine.frame = 0;
    engine.frameStart = SDL_GetTicks();
    engine.system = &system;

    // create game world
    theWorld = World();

    // create game entities
    // TODO: abstract this

    // player
    Vector3 playerPosition(200, 200, 0);
    Vector2 playerSize(50, 50);
    Color playerColor(0, 255, 255);
    Entity* player = DBG_NEW Entity();
    player->SetPosition(playerPosition);
    player->CreateRenderer(playerSize, playerColor);
    player->CreateCollider(playerSize.x / 2.0, playerSize.y / 2.0);
    player->CreatePlayerController();
    player->CreateColliderColorChanger(Color(0, 127, 255));
    gameEntities.push_back(player); // keep track of it

    // obstacle
    Vector3 obstaclePosition(windowSize.x / 2, windowSize.y / 2, 0);
    Vector2 obstacleSize(50, 200);
    Color obstacleColor(255, 0, 0);
    Entity* obstacle = DBG_NEW Entity();
    obstacle->SetPosition(obstaclePosition);
    obstacle->CreateRenderer(obstacleSize, obstacleColor);
    obstacle->CreateCollider(obstacleSize.x / 2.0, obstacleSize.y / 2.0);
    gameEntities.push_back(obstacle); // keep track of it

    // background
    Vector3 bgPosition(windowSize.x / 2, windowSize.y / 2, 0);
    Vector2 bgSize(windowSize.x, windowSize.y);
    Color bgColor(255, 255, 255);
    Entity* background = DBG_NEW Entity();
    background->SetPosition(bgPosition);
    background->CreateRenderer(bgSize, bgColor);
    gameEntities.push_back(background); // keep track of it

    // game is here
    runMainLoop(&engine);

    // cleanup
    cleanupGame();

    // quit game
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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
        renderGame((EngineState*)engine);

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
        getWorld()->colorchanger_array[i].Update(gameEntities[1]); // hard coded to check for the obstacle
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
    puts(frameStr);

    // display collider array!
    for (int i = 0; i < size; i++)
    {
        std::cout << colliderArray[i]->GetOwner()->GetTransform()->position.x << std::endl;
    }
}

void Game::renderGame(EngineState* engine)
{
    //int x = (SDL_sinf(engine->frame / 100.0f) * 100.0f) + 200;

    // clear screen
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(engine->renderer);

    /*
    // example: draw rect
    SDL_SetRenderDrawColor(engine->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(engine->renderer, &r);
    */

    // draw all entities
    for (int i = gameEntities.size() - 1; i >= 0; --i)
    {
        // work out windowSize and position
        Vector2 mySize = gameEntities[i]->GetRenderer()->GetSize();
        Vector2 myPos = (Vector2)gameEntities[i]->GetTransform()->position - (mySize / 2.0); // center the rect
        SDL_Rect rect = { myPos.x, myPos.y, mySize.x, mySize.y };

        // set color and draw
        Color myColor = gameEntities[i]->GetRenderer()->GetColor();
        SDL_SetRenderDrawColor(engine->renderer, myColor.r, myColor.g, myColor.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(engine->renderer, &rect);
    }

    // show changes
    SDL_RenderPresent(engine->renderer);
}
