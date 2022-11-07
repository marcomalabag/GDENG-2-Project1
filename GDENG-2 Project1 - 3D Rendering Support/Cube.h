#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "EngineTime.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "Matrix4x4.h"
#include "SceneCameraHandler.h"
#include "EngineTime.h"
#include "Shaderlibrary.h"


class Cube: public AGameObject
{
public:
	Cube(string name);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimSpeed(float speed);


private:
	VertexBuffer* verterbuffer;
	IndexBuffer* indexbuffer;
	ConstantBuffer* constantbuffer;
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

	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;
	int w, h;

	ShaderNames namesShader;
	Shaderlibrary::ShaderData shaderdata;
};

