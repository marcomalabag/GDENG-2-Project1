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
	else if(type == PrimitiveType::CARD)
	{
		Card* card = new Card("Card");
		card->setPosition(0.0f, 0.9f, 0.0f);
		card->setScale(1.0f, 1.0f, 1.0f);
		card->setRotation(1.0f, 0.0f, 0.0f);
		this->addObject(card);

		Card* card2 = new Card("Card2");
		card2->setPosition(0.0f, 0.9f, -0.2f);
		card2->setScale(1.0f, 1.0f, 1.0f);
		card2->setRotation(-1.0f, 0.0f, 0.0f);
		this->addObject(card2);

		Card* card3 = new Card("Card3");
		card3->setPosition(0.0f, 0.7f, -0.1f);
		card3->setScale(1.0f, 1.0f, 1.0f);
		card3->setRotation(0.0f, 0.0f, 0.0f);
		this->addObject(card3);

		Card* card4 = new Card("Card4");
		card4->setPosition(0.0f, 0.5f, 0.2f);
		card4->setScale(1.0f, 1.0f, 1.0f);
		card4->setRotation(1.0f, 0.0f, 0.0f);
		this->addObject(card4);

		Card* card5 = new Card("Card5");
		card5->setPosition(0.0f, 0.5f, 0.0f);
		card5->setScale(1.0f, 1.0f, 1.0f);
		card5->setRotation(-1.0f, 0.0f, 0.0f);
		this->addObject(card5);

		Card* card6 = new Card("Card6");
		card6->setPosition(0.0f, 0.3f, 0.1f);
		card6->setScale(1.0f, 1.0f, 1.0f);
		card6->setRotation(0.0f, 0.0f, 0.0f);
		this->addObject(card6);

		Card* card7 = new Card("Card7");
		card7->setPosition(0.0f, 0.5f, -0.2f);
		card7->setScale(1.0f, 1.0f, 1.0f);
		card7->setRotation(1.0f, 0.0f, 0.0f);
		this->addObject(card7);

		Card* card8 = new Card("Card8");
		card8->setPosition(0.0f, 0.5f, -0.41f);
		card8->setScale(1.0f, 1.0f, 1.0f);
		card8->setRotation(-1.0f, 0.0f, 0.0f);
		this->addObject(card8);

		Card* card9 = new Card("Card9");
		card9->setPosition(0.0f, 0.3f, -0.31f);
		card9->setScale(1.0f, 1.0f, 1.0f);
		card9->setRotation(0.0f, 0.0f, 0.0f);
		this->addObject(card9);

		Card* card10 = new Card("Card10");
		card10->setPosition(0.0f, 0.1f, 0.4f);
		card10->setScale(1.0f, 1.0f, 1.0f);
		card10->setRotation(1.0f, 0.0f, 0.0f);
		this->addObject(card10);

		Card* card11 = new Card("Card11");
		card11->setPosition(0.0f, 0.1f, 0.2f);
		card11->setScale(1.0f, 1.0f, 1.0f);
		card11->setRotation(-1.0f, 0.0f, 0.0f);
		this->addObject(card11);

		Card* card12 = new Card("Card12");
		card12->setPosition(0.0f, 0.1f, 0.0f);
		card12->setScale(1.0f, 1.0f, 1.0f);
		card12->setRotation(1.0f, 0.0f, 0.0f);
		this->addObject(card12);

		Card* card13 = new Card("Card13");
		card13->setPosition(0.0f, 0.1f, -0.2f);
		card13->setScale(1.0f, 1.0f, 1.0f);
		card13->setRotation(-1.0f, 0.0f, 0.0f);
		this->addObject(card13);

		Card* card14 = new Card("Card14");
		card14->setPosition(0.0f, 0.1f, -0.4f);
		card14->setScale(1.0f, 1.0f, 1.0f);
		card14->setRotation(1.0f, 0.0f, 0.0f);
		this->addObject(card14);

		Card* card15 = new Card("Card15");
		card15->setPosition(0.0f, 0.1f, -0.6f);
		card15->setScale(1.0f, 1.0f, 1.0f);
		card15->setRotation(-1.0f, 0.0f, 0.0f);
		this->addObject(card15);
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

void GameObjectManager::hundreadCubes()
{
	int max = 1.5f;
	int min = -2.5f;
	Math math;
	for (int i = 0; i < 100; i++)
	{
		String cubename;
		if (this->cubeCounter == 0)
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
	
}

void GameObjectManager::fiftyCubes()
{
	int max = 5.5f;
	int min = -5.5f;
	Math math;
	for (int i = 0; i < 50; i++)
	{
		String cubename;
		if (this->cubeCounter == 0)
		{
			cubename = "Cube";
		}
		else
		{
			String number = "(" + std::to_string(this->cubeCounter) + ")";
			cubename = "Cube" + number;
		}
		float x = math.getRandom(min, max);
		float y = math.getRandom(min, max);
		float speed = math.getRandom(1.0f, 25.0f);
		Cube* cube = new Cube(cubename);
		cube->setPosition(x, y, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		cube->setAnimSpeed(speed);
		this->addObject(cube);
		this->cubeCounter++;
	}
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return this->SelectedObject;
}



GameObjectManager::~GameObjectManager()
{
	delete this->SelectedObject;
	
}

