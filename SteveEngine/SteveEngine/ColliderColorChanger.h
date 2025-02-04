#pragma once

#include <istream>
#include <vector>

#include "Component.h"
#include "Utils.h"

class ColliderColorChanger : public Component
{
public:
	ColliderColorChanger();
	ColliderColorChanger(Entity* pOwner, const Color& color);

	void LoadFromFile(std::istream& file) override;

	void SetBaseColor(const Color& col) { baseColor = col; }
	void AutoSetBaseColor();
	void SetHitColor(const Color& col) { hitColor = col; }

	void Update(std::vector<Entity*> entsToCheck);

private:
	Color baseColor;
	Color hitColor;

};

