#include "RectangleCollider.h"
#include "Transform.h"
#include "Entity.h"

RectangleCollider::RectangleCollider()
{
	pOwner = nullptr;
	halfWidth = 0.0;
	halfHeight = 0.0;
}

RectangleCollider::RectangleCollider(Entity* pOwner, float halfWidth, float halfHeight)
{
	this->pOwner = pOwner;

	this->halfWidth = halfWidth;
	this->halfHeight = halfHeight;
}

RectangleCollider::RectangleCollider(Entity* pOwner, Vector2 halfExtents)
{
	this->pOwner = pOwner;

	this->halfWidth = halfExtents.x;
	this->halfHeight = halfExtents.y;
}

void RectangleCollider::LoadFromFile(std::istream& file)
{
	//file.ignore(100, (int)ComponentID::RectCollider);
	file >> this->halfWidth;
	file >> this->halfHeight;

	// ignore until the next component
	file.ignore(100, '|');
}

// returns true if pOther is colliding with this collider
// TODO: simplify the get calls here for readability
bool RectangleCollider::CheckCollision(RectangleCollider* pOther)
{
	bool collidingX = this->getTopLeft().x < pOther->getBottomRight().x && this->getBottomRight().x > pOther->getTopLeft().x;
	bool collidingY = this->getTopLeft().y < pOther->getBottomRight().y&& this->getBottomRight().y > pOther->getTopLeft().y;
	return collidingX && collidingY;
}

Vector2 RectangleCollider::getTopLeft()
{
	float x = pOwner->GetTransform()->position.x - halfWidth;
	float y = pOwner->GetTransform()->position.y - halfHeight;
	return Vector2(x, y);
}

Vector2 RectangleCollider::getBottomRight()
{
	float x = pOwner->GetTransform()->position.x + halfWidth;
	float y = pOwner->GetTransform()->position.y + halfHeight;
	return Vector2(x, y);
}
