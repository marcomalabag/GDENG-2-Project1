#pragma once
class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& vector);
	static Vector3D zeros();
	static Vector3D ones();
	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta);
	Vector3D operator*(float num);
	Vector3D operator+(Vector3D vector);
	~Vector3D();


public:
	float x, y, z;
};

