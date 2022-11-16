#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "SceneCameraHandler.h"
#include "Shaderlibrary.h"


class Sphere: public AGameObject
{
public:
	Sphere(string name);
	~Sphere();

	void draw(int width, int height) override;
	void update(float deltaTime) override;

private:
	VertexBuffer* verterbuffer;
	IndexBuffer* indexbuffer;
	ConstantBuffer* constantbuffer;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float speed = 10.0f;

	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;

	ShaderNames namesShader;
	Shaderlibrary::ShaderData shaderdata;
	
};

