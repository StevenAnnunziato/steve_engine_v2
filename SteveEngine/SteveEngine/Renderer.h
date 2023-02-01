#pragma once

#include "System.h"
#include <SDL2/SDL_syswm.h>
#include "bgfx/bgfx.h"

class Vector2;

class Renderer
{
public:
	// constructor and destructor
	Renderer();
	~Renderer();

	void init(const Vector2& windowSize);
	void cleanup();

	void renderGame();

	struct PosColorVertex
	{
		float x;
		float y;
		float z;
		uint32_t color;
	};

private:
	SDL_Window* sdlWindow;
	SDL_Renderer* sdlRenderer;

    // cube vertex data
    PosColorVertex cubeVertices[8] = {
		{-1.0f,  1.0f,  1.0f, 0xff000000 },
		{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
		{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
		{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
		{-1.0f,  1.0f, -1.0f, 0xffff0000 },
		{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
		{-1.0f, -1.0f, -1.0f, 0xffffff00 },
		{ 1.0f, -1.0f, -1.0f, 0xffffffff },
	};
    uint16_t cubeTriList[36] =
	{
		0, 1, 2,
		1, 3, 2,
		4, 6, 5,
		5, 6, 7,
		0, 2, 4,
		4, 2, 6,
		1, 5, 3,
		5, 7, 3,
		0, 4, 1,
		4, 5, 1,
		2, 3, 6,
		6, 3, 7,
	};
};

