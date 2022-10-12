#pragma once

#include "Component.h"
#include "Utils.h"

class Transform : public Component
{
public:
	Transform();
	Transform(float x, float y, float z);
	Transform(Vector3 position);

	Vector3 position;
};

