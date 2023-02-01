#pragma once

class Vector2;
struct SDL_Window;
struct SDL_Renderer;

class Renderer
{
public:
	// constructor and destructor
	Renderer();
	~Renderer();

	void init(const Vector2& windowSize);
	void cleanup();

	void renderGame();

private:
	SDL_Window* sdlWindow;
	SDL_Renderer* sdlRenderer;
};

