#pragma once

#include "Component.h"
#include "Utils.h"

class RectangleCollider : public Component
{
public:
	RectangleCollider(Entity* pOwner, float halfWidth, float halfHeight);
	RectangleCollider(Entity* pOwner, Vector2 halfExtents);

	// returns true if pOther is colliding with this collider
	bool CheckCollision(RectangleCollider* pOther);

private:
	float halfWidth;
	float halfHeight;

	Vector2 getTopLeft();
	Vector2 getBottomRight();

};

