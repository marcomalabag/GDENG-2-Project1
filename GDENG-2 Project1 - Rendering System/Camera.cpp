#include "Camera.h"
#include <iostream>

Camera::Camera(string name):AGameObject(name)
{
	this->setPosition(0.0f, 0.0f, -2.0f);
	//this->cameraFront = Vector3D(0.0f, 0.0f, -1.0f);
	//this->cameraUp = Vector3D(0.0f, 1.0f, 0.0f);
	InputSystem::getInstance()->addListener(this);
	this->updateViewMatrix();
}

void Camera::updateViewMatrix()
{

	Matrix4x4 worldCam;
	Matrix4x4 lookAt;
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

	//lookAt = Matrix4x4::lookAt(this->Position, this->Position + this->cameraFront, this->cameraUp);
	
	
	this->LocalMatrix = worldCam;
}

void Camera::defaultmode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		z += rate;
	
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::AerialMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		y += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		y -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::DownWardMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		y -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		y += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::RightViewMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		z += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::LeftViewMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		z += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::update(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.x;
	float y = localPos.y;
	float z = localPos.z;
	float moveSpeed = 10.0f;

	/*

	if (defaultBool) {

		this->defaultmode(deltaTime * moveSpeed, x, y, z);
	}
	
	if (this->getLocalRotation().y >= 0.07f) {
		defaultBool = false;
		this->RightViewMode(deltaTime * moveSpeed, x, y, z);
	}

	else if (this->getLocalRotation().y <= -0.07f) {
		defaultBool = false;
		this->LeftViewMode(deltaTime * moveSpeed, x, y, z);
	}

	else {
		
		defaultBool = true;
	}

	if (this->getLocalRotation().x <= -0.05f) {
		defaultBool = false;
		this->AerialMode(deltaTime * moveSpeed, x, y, z);
	}

	else {
		defaultBool = true;
	}

	*/
	
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
	if (key == 'U') {
		std::cout << "default mode is set";
		defaultBool = true;
		AerialBool = false;
		RightBool = false;
	}
	else if (key == 'I') {
		std::cout << "Aerial mode is set";
		defaultBool = false;
		AerialBool = true;
		RightBool = false;
	}
	else if (key == 'O') {
		std::cout << "Right view mode is set";
		defaultBool = false;
		AerialBool = false;
		RightBool = true;
	}
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
		std::cout << "X:" << x<< "\n";
		std::cout << "Y:" << y << "\n";
		
		
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
