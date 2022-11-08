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
		TexturedCube* Texcube = new TexturedCube("TexturedCube");
		Texcube->setPosition(0.0f, 1.0f, 0.0f);
		Texcube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(Texcube);
	}

}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->GameObjectTable.erase(gameObject->getName());
	int index = -1;
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		if(this->GameObjectList[i] == gameObject)
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

