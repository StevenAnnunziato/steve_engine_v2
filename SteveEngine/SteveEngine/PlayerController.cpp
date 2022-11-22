#include "Entity.h"

#include "PlayerController.h"
#include "Transform.h"

PlayerController::PlayerController()
{
	this->pOwner = nullptr;

	KEY_STATE = SDL_GetKeyboardState(nullptr);
}

PlayerController::PlayerController(Entity* pOwner)
{
	this->pOwner = pOwner;

	KEY_STATE = SDL_GetKeyboardState(nullptr);
}

void PlayerController::LoadFromFile(std::istream& file)
{
}

void PlayerController::Update()
{
	// set movement speeds and other values
	const int V_SPEED = 3;
	const int H_SPEED = 3;

	// update keyboard state
	SDL_PumpEvents();

	// left/right
	if (KEY_STATE[SDL_SCANCODE_LEFT])
	{
		pOwner->GetTransform()->position.x -= H_SPEED;
	}
	else if (KEY_STATE[SDL_SCANCODE_RIGHT])
	{
		pOwner->GetTransform()->position.x += H_SPEED;
	}

	// up/down
	if (KEY_STATE[SDL_SCANCODE_UP])
	{
		pOwner->GetTransform()->position.y -= V_SPEED;
	}
	else if (KEY_STATE[SDL_SCANCODE_DOWN])
	{
		pOwner->GetTransform()->position.y += V_SPEED;
	}
}
