#pragma once
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "AGameObject.h"

class EditorAction
{
public:
	EditorAction(AGameObject* gameObject);
	~EditorAction();

	AGameObject::String getOwnerName();
	Vector3D getStoredPosition();
	Vector3D getStoredScale();
	Vector3D getStoredRotation();
	Matrix4x4 getStoredMatrix();

private:
	AGameObject::String objectName;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
};

