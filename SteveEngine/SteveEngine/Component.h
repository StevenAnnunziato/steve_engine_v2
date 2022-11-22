#pragma once

#include <istream>

class Entity;

enum class ComponentID
{
	None, Transform, RectRenderer, RectCollider, PlayerController, ColliderColorChanger, NUM_IDS
};

class Component
{
public:
	Entity* GetOwner() { return pOwner; }
	void SetOwner(Entity* owner) { pOwner = owner; }
	
	virtual void LoadFromFile(std::istream& file) = 0;

protected:
	Entity* pOwner;

};

