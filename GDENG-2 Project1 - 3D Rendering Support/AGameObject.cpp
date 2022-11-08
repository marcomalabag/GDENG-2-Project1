#include "AGameObject.h"


AGameObject::AGameObject(String name)
{
	this->name = name;
	this->Position = Vector3D::zeros();
	this->Rotation = Vector3D::zeros();
	this->Scale = Vector3D::ones();
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->Position = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->Position = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->Position;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->Scale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->Scale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->Scale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->Rotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->Rotation = rot;
}

void AGameObject::setRotationX(float x)
{
	this->Rotation.x = x;
}

void AGameObject::setRotationY(float y)
{
	this->Rotation.y = y;
}

void AGameObject::setRotationz(float z)
{
	this->Rotation.z = z;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->Rotation;
}

String AGameObject::getName()
{
	return this->name;
}

void AGameObject::setObjectTexture(Texture* texture)
{
	this->texture = texture;
}

Texture* AGameObject::getObjectTexture()
{
	return this->texture;
}

void AGameObject::setTextureFlag()
{
	this->isTextured = true;
}

bool AGameObject::textureFlag()
{
	return this->isTextured;
}

AGameObject::~AGameObject()
{
	this->vertex_shader->release();
	this->pixel_shader->release();
}
