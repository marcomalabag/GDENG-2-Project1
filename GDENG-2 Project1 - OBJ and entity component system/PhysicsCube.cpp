#include "PhysicsCube.h"
#include "PhysicsComponent.h"
#include "Math.h"

PhysicsCube::PhysicsCube(String name): Cube(name)
{
	
	this->setPosition(Math::getRandom(0.1, 0.9), 6.0f, Math::getRandom(0.1, 0.9));
	this->setScale(1.5f, 1.5f, 1.5f);
	this->ComputeLocalMatrix();
	this->attachComponent(new PhysicsComponent("Physics Component", this));
}

void PhysicsCube::awake()
{
}

void PhysicsCube::draw(int width, int height)
{
	Cube::draw(width, height);
	
}

void PhysicsCube::update(float deltaTime)
{
	Cube::update(deltaTime);
}

PhysicsCube::~PhysicsCube()
{
	Cube::~Cube();
}


