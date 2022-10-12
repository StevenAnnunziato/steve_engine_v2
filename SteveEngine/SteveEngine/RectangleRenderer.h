#pragma once

#include "Component.h"
#include "Utils.h"

class RectangleRenderer : public Component
{

public:
	RectangleRenderer(Vector2 size, Color color);

private:
	Vector2 size;
	Color color;

};

