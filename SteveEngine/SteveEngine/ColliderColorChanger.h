#pragma once

#include "Component.h"
#include "Utils.h"

class ColliderColorChanger : public Component
{
public:
	ColliderColorChanger(Entity* pOwner);

	void Update(Entity* colliderToCheck);

private:
	Color baseColor;
	Color hitColor;

};

