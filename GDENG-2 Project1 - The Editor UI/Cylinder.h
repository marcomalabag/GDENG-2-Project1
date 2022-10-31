#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "SceneCameraHandler.h"

class Cylinder: public AGameObject
{
public:
	Cylinder(string name, void* ShaderByteCode, size_t SizeShader);
	void draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader) override;
	void update(float deltaTime) override;
	~Cylinder();

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

	Vector3D rotation;

	Matrix4x4 Summation;
	Matrix4x4 translate;
	Matrix4x4 Scale;

	Matrix4x4 RotationZ;
	Matrix4x4 RotationF;
	Matrix4x4 RotationGl;
	Matrix4x4 Rotation;

	Matrix4x4 RotationTotal;

	std::vector<vertex> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<Vector3D> CircleVertices;
	int BaseCenterIndex;
	int TopCenterIndex;
};

