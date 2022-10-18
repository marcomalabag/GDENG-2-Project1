#pragma once
#include "Cube.h"

class Plane : public Cube
{
public:
	Plane(string name, void* shaderByteCode, size_t sizeShader);
	~Plane();

	void draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader) override;
	


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
};

