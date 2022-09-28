//#include <crtdbg.h>


#include "System.h"
#include <iostream>

struct EngineState
{
    SDL_Renderer* renderer;
    SteveEngine::System* system;
    Uint32 frameStart;
    bool quit;
    int frame;
};

void runMainLoop(EngineState* engine);
void frameStep(void* arg);
Uint32 GetTicks();

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SteveEngine::System system;
    system.Init();

    int* leak = DBG_NEW int[4096];

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    EngineState engine;
    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = GetTicks();
    engine.system = &system;

    runMainLoop(&engine);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    system.Shutdown();
    return 0;
}

void handle_events(void* engine)
{
    Uint32 now = GetTicks();
    if (now - ((EngineState*)engine)->frameStart >= 16)
    {
        frameStep(((EngineState*)engine));
    }
}

void runMainLoop(EngineState* engine)
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(handle_events, engine, 0, true);
#else

    while (!engine->quit)
    {
        handle_events(engine);
    }
#endif
}

void frameStep(void* arg)
{
    EngineState* engine = (EngineState*)arg;
    SDL_Event event;

    Uint32 now = GetTicks();

    engine->frame++;
    engine->frameStart = now;

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

                // TODO: Add calls to ErrorMessage and LogToErrorFile here
                engine->system->ShowError(ERROR_K);
                engine->system->LogToErrorFile(ERROR_K);

            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                engine->quit = true;
            }
        }
    }

    int x = (SDL_sinf(engine->frame / 100.0f) * 100.0f) + 200;

    SDL_Rect r = {
        x,
        100,
        50,
        50
    };

    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderClear(engine->renderer);
    SDL_SetRenderDrawColor(engine->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(engine->renderer, &r);
    SDL_RenderPresent(engine->renderer);
}

Uint32 GetTicks()
{
    return SDL_GetTicks();
}