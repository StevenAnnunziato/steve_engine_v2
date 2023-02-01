#include "Renderer.h"

#include "Utils.h"
#include <iostream>

#include "System.h"
#include <SDL2/SDL_syswm.h>
#include "bgfx/bgfx.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::init(const Vector2& windowSize)
{
    // init sdl
    sdlWindow = NULL;
    sdlRenderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    sdlWindow = SDL_CreateWindow("SteveEngine3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.x, windowSize.y, SDL_WINDOW_SHOWN);
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);

    //get window information to pass along to bgfx
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(sdlWindow, &wmi)) {
        std::cout << "Error: Cannot get window data." << std::endl;
    }

    // init bgfx
    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.platformData.nwh = wmi.info.win.window;
    bgfxInit.platformData.ndt = NULL;
    bgfxInit.resolution.width = windowSize.x;
    bgfxInit.resolution.height = windowSize.y;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(bgfxInit);

    // clear buffers
    bgfx::reset(windowSize.x, windowSize.y, BGFX_RESET_VSYNC);
    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    // init view window
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, windowSize.x, windowSize.y);

    // add something so that BGFX renders
    bgfx::touch(0);
}

void Renderer::cleanup()
{
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);

    bgfx::shutdown();
}

void Renderer::renderGame()
{
    // show the frame
    bgfx::frame();
}
