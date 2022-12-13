#pragma once
#include "Cube.h"

class Plane : public Cube
{
public:
	Plane(String name);
	void setTexturesVertexBuffer();
	~Plane();

	void draw(int width, int height) override;

	
};

