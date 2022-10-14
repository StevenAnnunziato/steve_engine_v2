#pragma once

#include "Component.h"
#include "Utils.h"

class Transform : public Component
{
public:
	Transform();
	Transform(float x, float y, float z);
	Transform(Vector3 position);

	Transform operator=(const Transform& rhs)
	{
		Transform returnTransform;
		returnTransform.position.x = rhs.position.x;
		returnTransform.position.y = rhs.position.y;
		returnTransform.position.z = rhs.position.z;
		return returnTransform;
	}

	Vector3 position;
};

