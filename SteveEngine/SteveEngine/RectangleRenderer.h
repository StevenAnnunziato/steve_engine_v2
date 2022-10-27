#pragma once

#include "Component.h"
#include "Utils.h"

class RectangleRenderer : public Component
{

public:
	RectangleRenderer();
	RectangleRenderer(Entity* pOwner, Vector2 size, Color color);

	Vector2& GetSize() { return size; }
	Color& GetColor() { return color; }

	void SetSize(const Vector2& newSize) { size = newSize; }
	void SetColor(const Color& newColor) { color = newColor; }

private:
	Vector2 size;
	Color color;

};

