#pragma once

#include "Component.h"
#include "Utils.h"

class RectangleRenderer : public Component
{

public:
	RectangleRenderer(Vector2 size, Color color);

	Vector2 GetSize() { return size; }
	Color GetColor() { return color; }

private:
	Vector2 size;
	Color color;

};

