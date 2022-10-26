#include "RectangleRenderer.h"
#include "Utils.h"

RectangleRenderer::RectangleRenderer()
{
	this->pOwner = nullptr;

	this->size = Vector2();
	this->color = Color();
}

RectangleRenderer::RectangleRenderer(Entity* pOwner, Vector2 size, Color color)
{
	this->pOwner = pOwner;

	this->size = size;
	this->color = color;
}
