#include "Transform.h"


Transform::Transform()
{
	position = Vector3();
}

Transform::Transform(float x, float y, float z)
{
	position = Vector3(x, y, z);
}

Transform::Transform(Vector3 position)
{
	this->position = position;
}

void Transform::LoadFromFile(std::istream& file)
{
}
