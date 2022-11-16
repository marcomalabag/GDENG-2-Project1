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

void AGameObject::setLocalMatrix(float matrix[16])
{
	float Matrix[4][4];

	Matrix[0][0] = matrix[0];
	Matrix[0][1] = matrix[1];
	Matrix[0][2] = matrix[2];
	Matrix[0][3] = matrix[3];

	Matrix[1][0] = matrix[4];
	Matrix[1][1] = matrix[5];
	Matrix[1][2] = matrix[6];
	Matrix[1][3] = matrix[7];

	Matrix[2][0] = matrix[8];
	Matrix[2][1] = matrix[9];
	Matrix[2][2] = matrix[10];
	Matrix[2][3] = matrix[11];

	Matrix[3][0] = matrix[12];
	Matrix[3][1] = matrix[13];
	Matrix[3][2] = matrix[14];
	Matrix[3][3] = matrix[15];

	Matrix4x4 coordinate;
	coordinate.setMatrix(Matrix);

	Matrix4x4 scale;
	scale.setScale(this->Scale);

	Matrix4x4 translate;
	translate.setTranslation(this->Position);

	this->LocalMatrix = scale.mulMatrix(translate.mulMatrix(coordinate));
	
}

Matrix4x4 AGameObject::getLocalMatrix()
{
	return this->LocalMatrix;
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

AGameObject::String AGameObject::getName()
{
	return this->name;
}

void AGameObject::ComputeLocalMatrix()
{
	this->Summation.setIdentity();
	this->translate.setIdentity();
	this->ScaleMatrix.setIdentity();

	translate.setTranslation(this->getLocalPosition());
	ScaleMatrix.setScale(this->getLocalScale());
	rotation = Vector3D(this->getLocalRotation());

	this->RotationZ.setIdentity();
	this->RotationZ.setRotationZ(rotation.z);

	this->RotationF.setIdentity();
	this->RotationF.setRotationX(rotation.x);

	this->RotationGl.setIdentity();
	this->RotationGl.setRotationY(rotation.y);

	this->RotationTotal.setIdentity();
	this->RotationTotal = this->RotationTotal.mulMatrix(RotationF.mulMatrix(RotationGl.mulMatrix(RotationZ)));
	this->Summation = this->Summation.mulMatrix(ScaleMatrix.mulMatrix(this->RotationTotal));
	this->Summation = this->Summation.mulMatrix(this->translate);
	this->LocalMatrix = this->Summation;
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			this->componentList.erase(this->componentList.begin() + index);
			break;
		}
	}
}

AComponent* AGameObject::findComponentByName(String name)
{
	AComponent* found = nullptr;
	for(int i = 0; i < this->componentList.size(); i++)
	{
		if(this->componentList[i]->getName() == name)
		{
			found = this->componentList[i];
		}
	}
	return found;
}

AComponent* AGameObject::findComponentbyType(AComponent::ComponentType type, String name)
{
	AComponent* found = nullptr;
	for (int i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type)
		{
			found = this->componentList[i];
		}
	}
	return found;
}

AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++)
	{
		foundList.push_back(this->componentList[i]);
	}

	return foundList;
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

void AGameObject::awake()
{
}

AGameObject::~AGameObject()
{
	this->vertex_shader->release();
	this->pixel_shader->release();
}
