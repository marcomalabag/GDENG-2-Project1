#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "InputSystem.h"


class Camera: public AGameObject, public InputListener
{
public:
	Camera(string name);
	~Camera();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader) override;
	Matrix4x4 getViewMatrix();

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
};

