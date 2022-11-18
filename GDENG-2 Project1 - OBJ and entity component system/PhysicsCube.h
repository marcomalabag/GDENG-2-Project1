#pragma once
#include "Cube.h"
class PhysicsCube: public Cube
{
public:
	PhysicsCube(String name);
	void awake() override;
	void draw(int width, int height) override;
	void update(float deltaTime) override;
	~PhysicsCube();
};

