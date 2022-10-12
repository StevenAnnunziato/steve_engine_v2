#pragma once

#include "Transform.h"

class RectangleRenderer;
class RectangleCollider;
class PlayerController;
class ColliderColorChanger;

class Entity
{

public:
    Entity();

    RectangleRenderer* CreateRenderer();
    RectangleCollider* CreateCollider();
    PlayerController* CreatePlayerController();
    ColliderColorChanger* CreateColliderColorChanger();

    Transform GetTransform() { return transform; }
    RectangleRenderer* GetRenderer() { return rectRenderer; }
    RectangleCollider* GetCollider() { return rectCollider; }
    PlayerController* GetPlayerController() { return playerController; }
    ColliderColorChanger* GetColorChanger() { return colorChanger; }

protected:
    Transform transform;
    RectangleRenderer* rectRenderer;
    RectangleCollider* rectCollider;
    PlayerController* playerController;
    ColliderColorChanger* colorChanger;

};
