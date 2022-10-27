#include "Entity.h"
#include "Utils.h"

#include "Transform.h"
#include "RectangleRenderer.h"
#include "RectangleCollider.h"
#include "PlayerController.h"
#include "ColliderColorChanger.h"

#include "Game.h"

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
    // components are stored on the stack, so there is nothing to delete here
}

// Component creation - just get the next one preallocated from Game::World!

// TODO: Transform

RectangleRenderer* Entity::CreateRenderer(const Vector2& size, const Color& color)
{
    RectangleRenderer* rectRenderer = Game::getInstance()->getWorld()->GetNextRenderer();
    rectRenderer->SetOwner(this);
    rectRenderer->SetSize(size);
    rectRenderer->SetColor(color);
    this->rectRenderer = rectRenderer;
    return rectRenderer;
}

RectangleCollider* Entity::CreateCollider(const float& halfWidth, const float& halfHeight)
{
    RectangleCollider* rectCollider = Game::getInstance()->getWorld()->GetNextCollider();
    rectCollider->SetOwner(this);
    rectCollider->SetHalfWidth(halfWidth);
    rectCollider->SetHalfHeight(halfHeight);
    this->rectCollider = rectCollider;
    return rectCollider;
}

PlayerController* Entity::CreatePlayerController()
{
    PlayerController* playerController = Game::getInstance()->getWorld()->GetNextController();
    playerController->SetOwner(this);
    this->playerController = playerController;
    return playerController;
}

ColliderColorChanger* Entity::CreateColliderColorChanger(const Color& color)
{
    ColliderColorChanger* colorChanger = Game::getInstance()->getWorld()->GetNextColorChanger();
    colorChanger->SetOwner(this);
    colorChanger->SetHitColor(color);
    colorChanger->AutoSetBaseColor();
    this->colorChanger = colorChanger;
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
