#include "GameObjectManager.h"
#include "EngineTime.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager::GameObjectManager()
{
	this->SelectedObject = NULL;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::destroy()
{
	delete sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(string name)
{
	return this->GameObjectTable.at(name);
}

ObjectList GameObjectManager::getAllObjects()
{
	return this->GameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->GameObjectList.size();
}

void GameObjectManager::updateAll()
{
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->update(EngineTime::getDeltaTime());
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight)
{
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->draw(viewportWidth, viewportHeight);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	this->GameObjectTable[gameObject->getName()] = gameObject;
	this->GameObjectList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type)
{
	if(type == PrimitiveType::CUBE)
	{
		String cubename;
		if(this->cubeCounter == 0)
		{
			cubename = "Cube";
		}
		else
		{
			String number = "(" + std::to_string(this->cubeCounter) + ")";
			cubename = "Cube" + number;
		}
		Cube* cube = new Cube(cubename);
		cube->setPosition(0.0f, 1.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
		this->cubeCounter++;
	}
	else if (type == PrimitiveType::PLANE)
	{
		String planename;
		if (this->planeCounter == 0)
		{
			planename = "Plane";
		}
		else
		{
			String number = "(" + std::to_string(this->planeCounter) + ")";
			planename = "Plane" + number;
		}
		Plane* plane = new Plane(planename);
		plane->setPosition(0.0f, 1.0f, 0.0f);
		plane->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(plane);
		this->planeCounter++;
	}
	else if (type == PrimitiveType::CYLINDER)
	{
		String cylindername;
		if (this->cylinderCounter == 0)
		{
			cylindername = "Cylinder";
		}
		else
		{
			String number = "(" + std::to_string(this->cylinderCounter) + ")";
			cylindername = "Cylinder" + number;
		}
		Cylinder* cylinder = new Cylinder(cylindername);
		cylinder->setPosition(0.0f, 1.0f, 0.0f);
		cylinder->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cylinder);
		this->cylinderCounter++;
	}
	else if (type == PrimitiveType::SPHERE)
	{
		String spherename;
		if (this->sphereCounter == 0)
		{
			spherename = "Sphere";
		}
		else
		{
			String number = "(" + std::to_string(this->sphereCounter) + ")";
			spherename = "Sphere" + number;
		}
		Sphere* sphere = new Sphere(spherename);
		sphere->setPosition(0.0f, 1.0f, 0.0f);
		sphere->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(sphere);
		this->sphereCounter++;
	}
	else if(type == PrimitiveType::TEXTURED_CUBE)
	{
		String TexturedCubename;
		if(this->TexturedCubecounter == 0)
		{
			TexturedCubename = "Textured Cube";
		}
		else
		{
			String number = "(" + std::to_string(this->TexturedCubecounter) + ")";
			TexturedCubename = "Textured Cube" + number;
		}
		TexturedCube* Texcube = new TexturedCube(TexturedCubename);
		Texcube->setPosition(0.0f, 1.0f, 0.0f);
		Texcube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(Texcube);
		this->TexturedCubecounter++;
	}
	

}

void GameObjectManager::createOBJMODEL(OBJMODEL model)
{
	TextureFileName filename;
	if(model == OBJMODEL::TEAPOT)
	{
		Texture* tex = TextureLibrary::getInstance()->getTexture(filename.BRICK);
		Mesh* mesh = MeshManager::getInstance()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
		OBJStructure* teapot = new OBJStructure(mesh, tex, "Teapot");
		teapot->setPosition(0.0f, 1.0f, 0.0f);
		teapot->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(teapot);
	}
	else if(model == OBJMODEL::ARMADILLO)
	{
		Texture* tex = TextureLibrary::getInstance()->getTexture(filename.BRICK);
		Mesh* mesh = MeshManager::getInstance()->createMeshFromFile(L"Assets\\Meshes\\armadillo.obj");
		OBJStructure* armadillo = new OBJStructure(mesh, tex, "Armadillo");
		armadillo->setPosition(0.0f, 1.0f, 0.0f);
		armadillo->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(armadillo);
	}
	else if(model == OBJMODEL::BUNNY)
	{
		Texture* tex = TextureLibrary::getInstance()->getTexture(filename.BRICK);
		Mesh* mesh = MeshManager::getInstance()->createMeshFromFile(L"Assets\\Meshes\\bunny.obj");
		OBJStructure* bunny = new OBJStructure(mesh, tex, "Bunny");
		bunny->setPosition(0.0f, 1.0f, 0.0f);
		bunny->setScale(4.0f, 4.0f, 4.0f);
		this->addObject(bunny);
	}
	else if (model == OBJMODEL::STATUE)
	{
		Texture* tex = TextureLibrary::getInstance()->getTexture(filename.BRICK);
		Mesh* mesh = MeshManager::getInstance()->createMeshFromFile(L"Assets\\Meshes\\statue.obj");
		OBJStructure* statue = new OBJStructure(mesh, tex, "Statue");
		statue->setPosition(0.0f, 1.0f, 1.0f);
		statue->setScale(3.0f, 3.0f, 3.0f);
		this->addObject(statue);
	}
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->GameObjectTable.erase(gameObject->getName());
	int index = -1;
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		if(this->GameObjectList[i]->getName() == gameObject->getName())
		{
			index = i;
			this->GameObjectList.erase(this->GameObjectList.begin() + index);
			break;
		}
	}
}

void GameObjectManager::deleteObjectByName(string name)
{
	this->deleteObject(this->GameObjectTable.at(name));
}

void GameObjectManager::setSelectedObject(string name)
{
	this->setSelectedObject(this->GameObjectTable.at(name));
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	this->SelectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return this->SelectedObject;
}



GameObjectManager::~GameObjectManager()
{
	delete this->SelectedObject;
	
}

