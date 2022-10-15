#include "RectangleRenderer.h"
#include "Utils.h"

RectangleRenderer::RectangleRenderer(Entity* pOwner, Vector2 size, Color color)
{
	this->pOwner = pOwner;

	this->size = size;
	this->color = color;
}
