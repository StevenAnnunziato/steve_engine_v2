#include "ColliderColorChanger.h"
#include "RectangleCollider.h"
#include "RectangleRenderer.h"
#include "Entity.h"

ColliderColorChanger::ColliderColorChanger()
{
	this->pOwner = nullptr;

	baseColor = { 255, 127, 0 };
	hitColor = { 0, 127, 255 };
}

ColliderColorChanger::ColliderColorChanger(Entity* pOwner, const Color& color)
{
	this->pOwner = pOwner;

	baseColor = pOwner->GetRenderer()->GetColor();
	hitColor = color;
}

void ColliderColorChanger::LoadFromFile(std::istream& file)
{
	Color color;
	file >> color.r;
	file >> color.g;
	file >> color.b;
	this->hitColor = color;

	// ignore until the next component
	file.ignore(100, '|');
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
		pOwner->GetRenderer()->SetColor(hitColor);
	else
		pOwner->GetRenderer()->SetColor(baseColor);
}
