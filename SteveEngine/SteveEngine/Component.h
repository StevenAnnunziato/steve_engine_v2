#pragma once

class Entity;

class Component
{
public:
	Entity* GetOwner() { return pOwner; }

	// TODO: set pOwner somewhere

protected:
	Entity* pOwner;

};

