#pragma once
#include <iostream>
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <vector>

using namespace std;

class AGameObject
{
public:
	
	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color1;
	};

	_declspec(align(16))
		struct constant
	{
		Matrix4x4 world;
		Matrix4x4 view;
		Matrix4x4 projection;
		unsigned int time;
	};

	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationz(float z);
	Vector3D getLocalRotation();



protected:
	VertexShader* vertex_shader;
	PixelShader* pixel_shader;
	Vector3D Position;
	Vector3D Scale;
	Vector3D Rotation;
	string name;
};


