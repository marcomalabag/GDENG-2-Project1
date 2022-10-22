#include "Camera.h"
#include <iostream>

Camera::Camera(string name):AGameObject(name)
{
	this->setPosition(0.0f, 0.0f, -2.0f);
	InputSystem::getInstance()->addListener(this);
	this->updateViewMatrix();
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();

	Matrix4x4 temp;
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.x);
	worldCam = worldCam.mulMatrix(temp);

	temp.setRotationY(localRot.y);
	worldCam = worldCam.mulMatrix(temp);

	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.mulMatrix(temp);

	worldCam.getInverse();
	this->LocalMatrix = worldCam;
}

void Camera::update(float deltaTime)
{
	Vector3D localPosition = this->getLocalPosition();
	float x = localPosition.x;
	float y = localPosition.y;
	float z = localPosition.z;
	float moveSpeed = 10.0f;

	if(InputSystem::getInstance()->isKeyDown('W'))
	{
		z += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S'))
	{
		z -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A'))
	{
		x -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D'))
	{
		x += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader)
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->LocalMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point& deltaMousePos)
{
	if(this->RightMouseDown)
	{
		Vector3D localRotation = this->getLocalRotation();
		float x = localRotation.x;
		float y = localRotation.y;
		float z = localRotation.z;

		float speed = 0.005f;
		x += deltaMousePos.y * speed;
		y += deltaMousePos.x * speed;
		std::cout << "X:" <<x<< "\n";
		std::cout << "Y:" <<y<< "\n";

		this->setRotation(x, y, z);
		this->updateViewMatrix();
	}
	
	
}

void Camera::onLeftMouseDown(const Point& mousePosition)
{
}

void Camera::onLeftMouseUp(const Point& mousePosition)
{
}

void Camera::onRightMouseDown(const Point& mousePosition)
{
	this->RightMouseDown = true;
}

void Camera::onRightMouseUp(const Point& mousePosition)
{
	this->RightMouseDown = false;
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}
