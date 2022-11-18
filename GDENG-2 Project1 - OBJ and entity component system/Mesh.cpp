#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>

#include "GraphicsEngine.h"
#include "VertexMesh.h"

Mesh::Mesh(const wchar_t* full_path): Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warning;
	std::string error;

	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &full_path[0], wcslen(full_path), NULL, 0, NULL, NULL);
	std::string inputfile(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &full_path[0], -1, &inputfile[0], size_needed, NULL, NULL);

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warning, &error, inputfile.c_str());

	if (!error.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

	
	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = 0.0f;
				tinyobj::real_t ty = 0.0f;
				if(index.texcoord_index > 0)
				{
					tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}
				

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);

				list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

	Shaderlibrary::getInstance()->requestVertexShaderData(names.MESHLAYOUT_VERTEX_SHADER_NAME, 
		&dataShader.shaderByteCode,
		&dataShader.sizeShader);
	this->vertexBuffer = GraphicsEngine::getInstance()->createTexturedVertexBuffer();
	this->vertexBuffer->load(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), dataShader.shaderByteCode, dataShader.sizeShader);
	this->indexBuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	this->indexBuffer->load(&list_indices[0], (UINT)list_indices.size());

}

VertexBufferTextured* Mesh::getVertexBuffer()
{
	return this->vertexBuffer;
}

IndexBuffer* Mesh::getIndexBuffer()
{
	return this->indexBuffer;
}

Mesh::~Mesh()
{
}

