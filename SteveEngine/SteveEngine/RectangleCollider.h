#pragma once

#include "Component.h"
#include "Utils.h"

class RectangleCollider : public Component
{
public:
	RectangleCollider();
	RectangleCollider(Entity* pOwner, float halfWidth, float halfHeight);
	RectangleCollider(Entity* pOwner, Vector2 halfExtents);

	void SetHalfWidth(const float& v) { halfWidth = v; }
	void SetHalfHeight(const float& v) { halfHeight = v; }

	// returns true if pOther is colliding with this collider
	bool CheckCollision(RectangleCollider* pOther);

private:
	float halfWidth;
	float halfHeight;

	Vector2 getTopLeft();
	Vector2 getBottomRight();

};

