#pragma once

#include <istream>

class Entity;

class Component
{
public:
	Entity* GetOwner() { return pOwner; }
	void SetOwner(Entity* owner) { pOwner = owner; }
	
	virtual void LoadFromFile(std::istream& file) = 0;

protected:
	Entity* pOwner;

};

