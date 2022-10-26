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
		addedVec.y = this->y - rhs.y;
		return addedVec;
	}

	Vector2 operator*(const float scalar)
	{
		Vector2 scaledVec;
		scaledVec.x = this->x * scalar;
		scaledVec.y = this->y * scalar;
		return scaledVec;
	}

	Vector2 operator/(const float scalar)
	{
		Vector2 scaledVec;
		scaledVec.x = this->x / scalar;
		scaledVec.y = this->y / scalar;
		return scaledVec;
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

	operator Vector2() const
	{
		return Vector2(x, y);
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

	Vector3 operator*(const float scalar)
	{
		Vector3 scaledVec;
		scaledVec.x = this->x * scalar;
		scaledVec.y = this->y * scalar;
		scaledVec.z = this->z * scalar;
		return scaledVec;
	}

	Vector3 operator/(const float scalar)
	{
		Vector3 scaledVec;
		scaledVec.x = this->x / scalar;
		scaledVec.y = this->y / scalar;
		scaledVec.z = this->z / scalar;
		return scaledVec;
	}
};

class Color
{
public:
	int r;
	int g;
	int b;

	Color()
	{
		r = 0;
		g = 0;
		b = 0;
	}

	Color(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};