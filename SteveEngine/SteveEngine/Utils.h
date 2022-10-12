#pragma once

class Vector2
{
public:
	float x;
	float y;

	Vector2()
	{
		x = 0.0;
		y = 0.0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 operator+(const Vector2& rhs)
	{
		Vector2 addedVec;
		addedVec.x = this->x + rhs.x;
		addedVec.y = this->x + rhs.y;
		return addedVec;
	}

	Vector2 operator-(const Vector2& rhs)
	{
		Vector2 addedVec;
		addedVec.x = this->x - rhs.x;
		addedVec.y = this->x - rhs.y;
		return addedVec;
	}
};

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 operator+(const Vector3& rhs)
	{
		Vector3 addedVec;
		addedVec.x = this->x + rhs.x;
		addedVec.y = this->x + rhs.y;
		addedVec.z = this->x + rhs.z;
		return addedVec;
	}

	Vector3 operator-(const Vector3& rhs)
	{
		Vector3 addedVec;
		addedVec.x = this->x - rhs.x;
		addedVec.y = this->x - rhs.y;
		addedVec.z = this->x - rhs.z;
		return addedVec;
	}
};

class Color
{
public:
	int r;
	int g;
	int b;
};