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

Vector3D Vector3D::nomalize(const Vector3D& v)
{
	float length_of_v = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return Vector3D(v.x / length_of_v, v.y / length_of_v, v.z / length_of_v);
}

Vector3D Vector3D::cross(Vector3D v1, Vector3D v2)
{
	Vector3D crossproduct = { 0, 0, 0 };
	crossproduct.x = v1.y * v2.z - v1.z * v2.y;
	crossproduct.y = v1.x * v2.z - v1.z * v2.x;
	crossproduct.z = v1.x * v2.y - v1.y * v2.x;
	return crossproduct;
}

int Vector3D::Dot(Vector3D v1, Vector3D v2)
{
	int dproduct = 0;

	dproduct += v1.x * v2.x;
	dproduct += v1.y * v2.y;
	dproduct += v1.z * v2.z;
	return dproduct;
}

Vector3D Vector3D::operator*(float num)
{
	return Vector3D(x * num, y * num, z * num);
}


Vector3D Vector3D::operator+(Vector3D vector)
{
	return Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

Vector3D Vector3D::operator-(Vector3D vector)
{
	return Vector3D(x - vector.x, y - vector.y, z - vector.z);
}

Vector3D Vector3D::operator/(Vector3D vector)
{
	return Vector3D(x / vector.x, y / vector.y, z / vector.z);
}

Vector3D Vector3D::operator/(float num)
{
	return Vector3D(x / num, y / num, z / num);
}

Vector3D::~Vector3D()
{
}
