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

void ColliderColorChanger::Update(std::vector<Entity*> entsToCheck)
{
	// check all objects for collision
	bool collision = false;
	for (int i = 0; i < entsToCheck.size(); i++)
	{
		// don't check against myself
		if (entsToCheck[i] == pOwner)
			continue;

		// don't check against entities that do not have a collider
		if (entsToCheck[i]->GetCollider() == nullptr)
			continue;

		// check collisions between the two objects
		if (pOwner->GetCollider()->CheckCollision(entsToCheck[i]->GetCollider()))
		{
			collision = true;
			break;
		}
	}

	if (collision)
		pOwner->GetRenderer()->SetColor(hitColor);
	else
		pOwner->GetRenderer()->SetColor(baseColor);
}
