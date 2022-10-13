#include <iostream>

#include "Game.h"
#include "Utils.h"

Game::Game()
{
}

Game::~Game()
{
}

// TODO: Reformat to put RunMainLoop and cleanup fns in another place!
void Game::initGame(const Vector2& size)
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SteveEngine::System system;
    system.Init();

    int* leak = DBG_NEW int[4096];

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    EngineState engine;
    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = SDL_GetTicks();
    engine.system = &system;

    // game is here
    runMainLoop(&engine);

    // quit game
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    system.Shutdown();
}

void Game::cleanupGame()
{
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

// physics and rendering
void Game::updateGameState(void* arg)
{
    EngineState* engine = (EngineState*)arg;
    SDL_Event event;

    // TODO: move this block to timing
    Uint32 now = SDL_GetTicks();
    engine->frame++;
    engine->frameStart = now;
    // --------------------------------

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
    int x = (SDL_sinf(engine->frame / 100.0f) * 100.0f) + 200;

    SDL_Rect r = {
        x,
        150,
        50,
        50
    };

    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderClear(engine->renderer);
    SDL_SetRenderDrawColor(engine->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(engine->renderer, &r);
    SDL_RenderPresent(engine->renderer);
}
