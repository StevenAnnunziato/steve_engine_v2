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

Entity::~Entity()
{
    delete rectRenderer;
    rectRenderer = nullptr;

    delete rectCollider;
    rectCollider = nullptr;

    delete playerController;
    playerController = nullptr;

    delete colorChanger;
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

void Entity::SetPosition(Vector3 position)
{
    transform.position = position;
}

void Entity::SetPosition(float x, float y, float z)
{
    transform.position = Vector3(x, y, z);
}
