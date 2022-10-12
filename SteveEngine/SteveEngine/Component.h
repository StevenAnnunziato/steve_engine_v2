#pragma once

class Entity;

class Component
{
public:
	Entity* GetOwner() { return pOwner; }

private:
	Entity* pOwner;

};

