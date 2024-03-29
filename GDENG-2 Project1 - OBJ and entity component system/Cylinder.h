#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "SceneCameraHandler.h"
#include "Shaderlibrary.h"

class Cylinder: public AGameObject
{
public:
	Cylinder(String name);
	void draw(int width, int height) override;
	void update(float deltaTime) override;
	void saveEditState() override;
	void restoreEditState() override;
	~Cylinder();

private:
	VertexBuffer* verterbuffer;
	VertexBufferTextured* verterBufferTextured;
	IndexBuffer* indexbuffer;
	ConstantBuffer* constantbuffer;

	float ticks = 0.0f;
	float speed = 10.0f;

	std::vector<vertex> Vertices;
	std::vector<Vertex> verticesTextured;
	std::vector<unsigned int> Indices;
	std::vector<Vector3D> CircleVertices;
	int BaseCenterIndex;
	int TopCenterIndex;

	ShaderNames namesShader;
	Shaderlibrary::ShaderData shaderdata;
	Shaderlibrary::ShaderData shaderdataTexture;
};

