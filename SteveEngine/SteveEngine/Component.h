#pragma once

class Entity;

class Component
{
public:
	Entity* GetOwner() { return pOwner; }

protected:
	Entity* pOwner;

};

