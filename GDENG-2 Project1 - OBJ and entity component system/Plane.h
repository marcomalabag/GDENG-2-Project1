#pragma once
#include "Cube.h"

class Plane : public Cube
{
public:
	Plane(String name);
	~Plane();

	void draw(int width, int height) override;

	
};

