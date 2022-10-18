#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "EngineTime.h"
#include "InputListener.h"
#include "InputSystem.h"


class Cube: public AGameObject, public InputListener
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader) override;
	void setAnimSpeed(float speed);

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& deltaMousePos) override;
	virtual void onLeftMouseDown(const Point& mousePosition) override;
	virtual void onLeftMouseUp(const Point& mousePosition) override;
	virtual void onRightMouseDown(const Point& mousePosition) override;
	virtual void onRightMouseUp(const Point& mousePosition) override;


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
};

