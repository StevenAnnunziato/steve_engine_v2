#pragma once

#include "Component.h"
#include "Utils.h"

class RectangleCollider : public Component
{
public:
	RectangleCollider(Vector2 topLeft, Vector2 bottomRight);

	// returns true if pOther is colliding with this collider
	bool CheckCollision(RectangleCollider* pOther);

private:
	Vector2 topLeft;
	Vector2 bottomRight;

};

