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

    int* leak = DBG_NEW int[4096];

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.x, windowSize.y, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    EngineState engine;
    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = SDL_GetTicks();
    engine.system = &system;

    // create game entities
    // TODO: abstract this

    // player
    Vector3 playerPosition(200, 200, 0);
    Vector2 playerSize(50, 50);
    Color playerColor(0, 255, 255);
    Entity* player = new Entity();
    player->SetPosition(playerPosition);
    player->CreateRenderer(playerSize, playerColor);
    player->CreateCollider(playerSize.x / 2.0, playerSize.y / 2.0);
    player->CreatePlayerController();
    player->CreateColliderColorChanger();
    gameEntities.push_back(player); // keep track of it

    // obstacle
    Vector3 obstaclePosition(windowSize.x / 2, windowSize.y / 2, 0);
    Vector2 obstacleSize(50, 200);
    Color obstacleColor(255, 0, 0);
    Entity* obstacle = new Entity();
    obstacle->SetPosition(obstaclePosition);
    obstacle->CreateRenderer(obstacleSize, obstacleColor);
    obstacle->CreateCollider(obstacleSize.x / 2.0, obstacleSize.y / 2.0);
    gameEntities.push_back(obstacle); // keep track of it

    // background
    Vector3 bgPosition(windowSize.x / 2, windowSize.y / 2, 0);
    Vector2 bgSize(windowSize.x, windowSize.y);
    Color bgColor(255, 255, 255);
    Entity* background = new Entity();
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
        spTheGame = new Game();
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

    // update all components
    for (int i = 0; i < gameEntities.size(); i++)
    {
        // update player controller
        if (gameEntities[i]->GetPlayerController() != nullptr)
            gameEntities[i]->GetPlayerController()->Update();

        // update color changer
        if (gameEntities[i]->GetColorChanger() != nullptr)
            gameEntities[i]->GetColorChanger()->Update();
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
