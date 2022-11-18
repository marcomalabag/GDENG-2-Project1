#include "PhysicsCube.h"
#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(String name): Cube(name)
{
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


