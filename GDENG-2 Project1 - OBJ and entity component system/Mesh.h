#pragma once

#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferTextured.h"
#include "Shaderlibrary.h"

class DeviceContext;
class Mesh: public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	VertexBufferTextured* getVertexBuffer();
	IndexBuffer* getIndexBuffer();

private:
	Shaderlibrary::ShaderData dataShader;
	VertexBufferTextured* vertexBuffer;
	IndexBuffer* indexBuffer;
	ShaderNames names;

private:
	friend class DeviceContext;
	

};

