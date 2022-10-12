#include "RectangleCollider.h"

RectangleCollider::RectangleCollider(Vector2 topLeft, Vector2 bottomRight)
{
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
}

// returns true if pOther is colliding with this collider
bool RectangleCollider::CheckCollision(RectangleCollider* pOther)
{
	bool collidingX = this->topLeft.x < pOther->bottomRight.x && this->bottomRight.x > pOther->topLeft.x;
	bool collidingY = this->topLeft.y < pOther->bottomRight.y && this->bottomRight.y > pOther->topLeft.y;
	return collidingX && collidingY;
}
