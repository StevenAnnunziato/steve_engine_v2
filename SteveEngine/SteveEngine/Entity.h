#pragma once

#include "Transform.h"

class RectangleRenderer;
class RectangleCollider;
class PlayerController;
class ColliderColorChanger;

class Vector2;
class Color;

class Entity
{

public:
    Entity();
    ~Entity();

    // Create components
    RectangleRenderer* CreateRenderer(const Vector2& size, const Color& color);
    RectangleCollider* CreateCollider(const float& halfWidth, const float& halfHeight);
    PlayerController* CreatePlayerController();
    ColliderColorChanger* CreateColliderColorChanger(const Color& color);

    // Getters
    Transform* GetTransform() { return &transform; }
    RectangleRenderer* GetRenderer() { return rectRenderer; }
    RectangleCollider* GetCollider() { return rectCollider; }
    PlayerController* GetPlayerController() { return playerController; }
    ColliderColorChanger* GetColorChanger() { return colorChanger; }

    // Shortcuts for setting position
    void SetPosition(Vector3 position);
    void SetPosition(float x, float y, float z);

protected:
    Transform transform;
    RectangleRenderer* rectRenderer;
    RectangleCollider* rectCollider;
    PlayerController* playerController;
    ColliderColorChanger* colorChanger;

};
