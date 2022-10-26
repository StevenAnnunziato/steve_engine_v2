#pragma once

class Entity;

class Component
{
public:
	Entity* GetOwner() { return pOwner; }
	void SetOwner(Entity* owner) { pOwner = owner; }
	
protected:
	Entity* pOwner;

};

