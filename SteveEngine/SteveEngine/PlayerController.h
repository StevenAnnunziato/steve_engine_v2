#pragma once

#include "Component.h"
#include "SDL2/SDL.h"


class PlayerController : public Component
{
public:
	PlayerController(Entity* pOwner);

	void Update();

private:
	const Uint8* KEY_STATE;
};

