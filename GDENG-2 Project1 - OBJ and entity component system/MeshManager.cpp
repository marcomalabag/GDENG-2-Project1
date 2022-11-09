#include "MeshManager.h"
#include <filesystem>
#include <iostream>

MeshManager* MeshManager::sharedInstance = NULL;

MeshManager::MeshManager() : ResourceManager()
{

}


MeshManager* MeshManager::getInstance()
{
	return sharedInstance;
}

void MeshManager::initialize()
{
	sharedInstance = new MeshManager();
}

Mesh* MeshManager::createMeshFromFile(const wchar_t* file_path)
{
	std::wstring full_path = std::filesystem::absolute(file_path);
	if (this->m_map_resources[full_path] == NULL)
	{
		this->m_map_resources[full_path] = this->createResourceFromFileConcrete(file_path);
	}

	return (Mesh*)this->m_map_resources[full_path];
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path);
	}
	catch (...) {}

	return mesh;
}

MeshManager::~MeshManager()
{
}

