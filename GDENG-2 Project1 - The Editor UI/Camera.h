#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "Math.h"
#include <cmath>
#include "EngineTime.h"



class Camera: public AGameObject, public InputListener
{
public:
	Camera(string name);
	~Camera();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader) override;
	Matrix4x4 getViewMatrix();

	void defaultmode(float rate, float x, float y, float z);
	void AerialMode(float rate, float x, float y, float z);
	void DownWardMode(float rate, float x, float y, float z);
	void RightViewMode(float rate, float x, float y, float z);
	void LeftViewMode(float rate, float x, float y, float z);

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& deltaMousePos) override;
	virtual void onLeftMouseDown(const Point& mousePosition) override;
	virtual void onLeftMouseUp(const Point& mousePosition) override;
	virtual void onRightMouseDown(const Point& mousePosition) override;
	virtual void onRightMouseUp(const Point& mousePosition) override;

	void updateViewMatrix();

private:
	Matrix4x4 LocalMatrix;
	bool RightMouseDown;
	float rate;
	Vector3D cameraFront;
	Vector3D cameraUp;
	float yaw = -90.0f;	
	float pitch = 0.0f;
	Vector3D center;

	bool defaultBool = true;
	bool AerialBool = false;
	bool RightBool = false;
};

