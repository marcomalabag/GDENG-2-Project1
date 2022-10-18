#include "Vector3D.h"

Vector3D::Vector3D()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D(const Vector3D& vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}

Vector3D Vector3D::zeros()
{
	return Vector3D(0.0f, 0.0f, 0.0f);
}

Vector3D Vector3D::ones()
{
	return Vector3D(1.0f, 1.0f, 1.0f);
}



Vector3D Vector3D::lerp(const Vector3D& start, const Vector3D& end, float delta)
{
	Vector3D vector;
	vector.x = start.x * (1.0f - delta) + end.x * (delta);
	vector.y = start.y * (1.0f - delta) + end.y * (delta);
	vector.z = start.z * (1.0f - delta) + end.z * (delta);
	return vector;
}


Vector3D::~Vector3D()
{
}
