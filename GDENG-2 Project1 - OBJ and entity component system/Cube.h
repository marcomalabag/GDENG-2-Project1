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
#include "Vector2D.h"



class Cube: public AGameObject
{
public:
	Cube(String name, AGameObject::PrimitiveType type);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimSpeed(float speed);
	void saveEditState() override;
	void restoreEditState() override;
	void setTexturesVertexBuffer();
	


protected:
	VertexBuffer* verterbuffer;
	VertexBufferTextured* textureVertexBuffer;
	IndexBuffer* indexbuffer;
	IndexBuffer* IndexBufferTexture;
	ConstantBuffer* constantbuffer;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float speed = 10.0f;

	ShaderNames namesShader;
	Shaderlibrary::ShaderData shaderdata;
	Shaderlibrary::ShaderData shaderdataTexture;
	
};

