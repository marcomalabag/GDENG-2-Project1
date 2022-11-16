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
	Cube(String name);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimSpeed(float speed);


protected:
	VertexBuffer* verterbuffer;
	
	IndexBuffer* indexbuffer;
	ConstantBuffer* constantbuffer;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float speed = 10.0f;

	ShaderNames namesShader;
	Shaderlibrary::ShaderData shaderdata;
};

