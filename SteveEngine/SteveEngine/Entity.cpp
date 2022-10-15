#include "Entity.h"
#include "Utils.h"

#include "Transform.h"
#include "RectangleRenderer.h"
#include "RectangleCollider.h"
#include "PlayerController.h"
#include "ColliderColorChanger.h"

Entity::Entity()
{
	// Initialize all components to nullptr
    transform = {0, 0, 0 };
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

RectangleRenderer* Entity::CreateRenderer(Vector2 size, Color color)
{
    rectRenderer = new RectangleRenderer(this, size, color);
    return rectRenderer;
}

RectangleCollider* Entity::CreateCollider(float halfWidth, float halfHeight)
{
    rectCollider = new RectangleCollider(this, halfWidth, halfHeight);
    return rectCollider;
}

PlayerController* Entity::CreatePlayerController()
{
    playerController = new PlayerController(this);
    return playerController;
}

ColliderColorChanger* Entity::CreateColliderColorChanger()
{
    colorChanger = new ColliderColorChanger(this);
    return colorChanger;
}

void Entity::SetPosition(Vector3 position)
{
    transform.position = position;
}

void Entity::SetPosition(float x, float y, float z)
{
    transform.position = Vector3(x, y, z);
}
