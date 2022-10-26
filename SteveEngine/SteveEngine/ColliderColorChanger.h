#pragma once

#include "Component.h"
#include "Utils.h"

class ColliderColorChanger : public Component
{
public:
	ColliderColorChanger();
	ColliderColorChanger(Entity* pOwner);

	void SetBaseColor(const Color& col) { baseColor = col; }
	void AutoSetBaseColor();
	void SetHitColor(const Color& col) { hitColor = col; }

	void Update(Entity* colliderToCheck);

private:
	Color baseColor;
	Color hitColor;

};

