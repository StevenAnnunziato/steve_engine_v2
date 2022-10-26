#include "ColliderColorChanger.h"
#include "RectangleCollider.h"
#include "RectangleRenderer.h"
#include "Entity.h"

#include <iostream>

ColliderColorChanger::ColliderColorChanger()
{
	this->pOwner = nullptr;

	baseColor = { 255, 127, 0 };
	hitColor = { 0, 127, 255 };
}

ColliderColorChanger::ColliderColorChanger(Entity* pOwner)
{
	this->pOwner = pOwner;

	baseColor = pOwner->GetRenderer()->GetColor();
	hitColor = { 0, 127, 255 };
}

void ColliderColorChanger::AutoSetBaseColor()
{
	baseColor = pOwner->GetRenderer()->GetColor();
}

void ColliderColorChanger::Update(Entity* colliderToCheck)
{
	// check collisions between the two objects
	bool collision = pOwner->GetCollider()->CheckCollision(colliderToCheck->GetCollider());

	if (collision)
		std::cout << "hit" << std::endl;
	else
		std::cout << "nope" << std::endl;

	if (collision)
		pOwner->GetRenderer()->SetColor(hitColor);
	else
		pOwner->GetRenderer()->SetColor(baseColor);
}
