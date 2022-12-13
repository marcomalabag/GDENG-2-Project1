#pragma once
#include "Cube.h"
#include "Vector2D.h"
#include "Texture.h"
#include "TextureManager.h"
#include "VertexBufferTextured.h"
#include "Texture.h"

class TexturedCube: public Cube
{
public:
	TexturedCube(String name);
	~TexturedCube();

	void draw(int width, int height) override;
	void update(float deltaTime) override;

	

private:
	VertexBufferTextured* vertexBuffer;
	IndexBuffer* index_Buffer;
	ConstantBuffer* constant_Buffer;
};

