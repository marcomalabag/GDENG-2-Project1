#include "VertexMesh.h"

VertexMesh::VertexMesh()
{
	this->m_position = Vector3D(0.0f, 0.0f, 0.0f);
	this->m_texcoord = Vector2D(0.0f, 0.0f);
}

VertexMesh::VertexMesh(Vector3D position, Vector2D texcoord)
{
	this->m_position = position;
	this->m_texcoord = texcoord;
}

VertexMesh::VertexMesh(const VertexMesh& vertex)
{
	this->m_position = vertex.m_position;
	this->m_texcoord = vertex.m_texcoord;
}

VertexMesh::~VertexMesh()
{
}
