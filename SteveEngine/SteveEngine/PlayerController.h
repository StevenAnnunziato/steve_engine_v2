#pragma once

#include <istream>

#include "Component.h"
#include "SDL2/SDL.h"


class PlayerController : public Component
{
public:
	PlayerController();
	PlayerController(Entity* pOwner);

	void LoadFromFile(std::istream& file) override;

	void Update();

private:
	const Uint8* KEY_STATE;
};

