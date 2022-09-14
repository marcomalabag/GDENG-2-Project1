#pragma once
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"

class Triangle
{
public:
	Triangle(void* shader_byte_code, size_t size_shader, VertexShader* vertexShader);
	void draw();
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

};

