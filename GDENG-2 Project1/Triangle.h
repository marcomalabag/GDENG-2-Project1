#pragma once
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "Matrix4x4.h"

class Triangle
{
public:
	Triangle();
	void draw();
	void setWindowSizeLength(float windowsizelength);
	void setWindowSizeHeight(float windowsizeheight);
	void setPosition(Vector3D Position);
	~Triangle();

private:
	VertexBuffer* vertexbuffer;
	VertexShader* vertexshader;
	PixelShader* pixelshader;
	ConstantBuffer* constantbuffer;

private:
	unsigned long oldTime = 0;
	float deltaTime = 0;
	float angle = 0;

	float windowSizeHeight;
	float windowSizeLength;

	Vector3D position;
	Vector3D scale;

};

