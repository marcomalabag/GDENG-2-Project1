#pragma once
#include "AGameObject.h"
#include "Shaderlibrary.h"
#include "Mesh.h"
#include "MeshManager.h"
#include "TextureLibrary.h"
#include "ConstantBuffer.h"
#include "SceneCameraHandler.h"

class Teapot: public AGameObject
{
public:
	Teapot(String name);
	~Teapot();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

private:
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float oldDelta = 0.0f;
	float newDelta = 0.0f;
	float speed = 10.0f;
	float rate = 3.14;

	Vector3D rotation;

	Matrix4x4 Summation;
	Matrix4x4 translate;
	Matrix4x4 Scale;

	Matrix4x4 RotationZ;
	Matrix4x4 RotationF;
	Matrix4x4 RotationGl;
	Matrix4x4 Rotation;

	Matrix4x4 RotationTotal;
	ShaderNames namesShader;
	Mesh* teapot;
	ConstantBuffer* constantbuffer;
	TextureFileName filenames;
};

