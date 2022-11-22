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

void RectangleRenderer::LoadFromFile(std::istream& file)
{
	//file.ignore(100, (int)ComponentID::RectRenderer);
	Vector2 size;
	Color color;

	file >> size.x;
	file >> size.y;
	file >> color.r;
	file >> color.g;
	file >> color.b;

	this->SetSize(size);
	this->SetColor(color);

	// ignore until the next component
	file.ignore(100, '|');
}
