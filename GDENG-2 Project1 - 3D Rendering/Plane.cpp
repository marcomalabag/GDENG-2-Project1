#include "Plane.h"

Plane::Plane(string name, void* shaderByteCode, size_t sizeShader): Cube(name, shaderByteCode,  sizeShader)
{
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,0.0f,-0.5f),    Vector3D(0.0,1,1),  Vector3D(1.0f,1.0f,1.0f) },
		{ Vector3D(-0.5f,0.0f,0.5f),   Vector3D(1,1,1),  Vector3D(1.0f,1.0f,1.0f) },
		{ Vector3D(0.5f,0.0f,0.5f),     Vector3D(1,1,1), Vector3D(1.0f,1.0f,1.0f) },
		{ Vector3D(0.5f,0.0f,-0.5f),    Vector3D(1,1,1), Vector3D(1.0f,1.0f,1.0f) },
		
	};

	this->verterbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->verterbuffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		0,1,2,  
		2,3,0
	};

	this->indexbuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->indexbuffer->load(index_list, size_index_list);
	constant cc;
	cc.time = 0;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));
}

Plane::~Plane()
{
	this->constantbuffer->release();
	this->indexbuffer->release();
	this->verterbuffer->release();
}


