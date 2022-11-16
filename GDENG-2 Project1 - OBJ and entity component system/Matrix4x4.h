#pragma once
#include <memory>
#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4x4
{
public:
	Matrix4x4();
	void setIdentity();
	void setTranslation(const Vector3D& translation);
	void setScale(const Vector3D& scale);
	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);
	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar);
	Vector3D getXDirection();
	Vector3D getZDirection();
	Vector3D getTranslation();
	float getDeterminant();
	void getInverse();
	void operator*=(const Matrix4x4& matrix);
	void setMatrix(const Matrix4x4& matrix);
	void setMatrix(float matrix[4][4]);
	Matrix4x4 getScalar(int constant);
	Matrix4x4 mulMatrix(Matrix4x4 in);
	void setOrthoLH(float width, float height, float near_plane, float far_plane);
	static Matrix4x4 lookAt(Vector3D eye, Vector3D center, Vector3D up);
	~Matrix4x4();

public:
	float Matrix[4][4] = {};
};

