#include "Entity.h"

#include "RectangleRenderer.h"
#include "RectangleCollider.h"
#include "PlayerController.h"
#include "ColliderColorChanger.h"

Entity::Entity()
{
	// Initialize all components to nullptr
    // transform = 
    rectRenderer = nullptr;
    rectCollider = nullptr;
    playerController = nullptr;
    colorChanger = nullptr;
}

RectangleRenderer* Entity::CreateRenderer()
{
    return nullptr;
}

RectangleCollider* Entity::CreateCollider()
{
    return nullptr;
}

PlayerController* Entity::CreatePlayerController()
{
    return nullptr;
}

ColliderColorChanger* Entity::CreateColliderColorChanger()
{
    return nullptr;
}
