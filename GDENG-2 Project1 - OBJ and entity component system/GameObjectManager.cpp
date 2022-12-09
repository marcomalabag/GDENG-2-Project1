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

AGameObject* GameObjectManager::findObjectByName(String name)
{
	return this->GameObjectTable.at(name);
}

GameObjectManager::ObjectList GameObjectManager::getAllObjects()
{
	return this->GameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->GameObjectList.size();
}

void GameObjectManager::updateAll()
{
	for(AGameObject* gameobject: this->GameObjectList)
	{
		for(AComponent* component: gameobject->getComponentsOfType(AComponent::Physics))
		{
			component->perform(EngineTime::getDeltaTime());
		}
	}
	/*
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->update(EngineTime::getDeltaTime());
	}
	*/
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
	if (this->GameObjectTable[gameObject->getName()] != NULL) {
		int count = 1;
		String revisedString = gameObject->getName() + "(" + std::to_string(count) + ")";
		while (this->GameObjectTable[revisedString] != NULL) {
			count++;
			revisedString = gameObject->getName() + "(" + std::to_string(count) + ")";
		}
		gameObject->setName(revisedString);
		this->GameObjectTable[revisedString] = gameObject;
	}
	else {
		this->GameObjectTable[gameObject->getName()] = gameObject;
	}
	
	this->GameObjectList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type)
{
	if(type == PrimitiveType::CUBE)
	{
		
		Cube* cube = new Cube("Cube", AGameObject::CUBE);
		cube->setPosition(0.0f, 1.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
		
	}
	else if (type == PrimitiveType::PLANE)
	{
		Plane* plane = new Plane("Plane");
		plane->setPosition(0.0f, 1.0f, 0.0f);
		plane->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(plane);
		
	}
	else if (type == PrimitiveType::CYLINDER)
	{
		Cylinder* cylinder = new Cylinder("Cylinder");
		cylinder->setPosition(0.0f, 1.0f, 0.0f);
		cylinder->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cylinder);
		
	}
	else if (type == PrimitiveType::SPHERE)
	{
		Sphere* sphere = new Sphere("Sphere");
		sphere->setPosition(0.0f, 1.0f, 0.0f);
		sphere->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(sphere);
	
	}
	else if(type == PrimitiveType::CAPSULE)
	{
		Capsule* capsule = new Capsule("Capsule");
		capsule->setPosition(0.0f, 1.0f, 0.0f);
		capsule->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(capsule);
	}
	else if(type == PrimitiveType::TEXTURED_CUBE)
	{
		TexturedCube* Texcube = new TexturedCube("Textured Cube");
		Texcube->setPosition(0.0f, 1.0f, 0.0f);
		Texcube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(Texcube);
	}
	else if(type == PrimitiveType::CAPSULE)
	{
		Capsule* capsule = new Capsule("Capsule");
		capsule->setPosition(0.0f, 1.0f, 0.0f);
		capsule->setScale(0.25f, 0.25f, 0.25f);
		this->addObject(capsule);
	}
	else if(type == PrimitiveType::PHYSICS_CUBE)
	{
		PhysicsCube* physicsCube = new PhysicsCube("Physics Cube");
		this->addObject(physicsCube);
	}
	else if(type == PrimitiveType::PHYSICS_PLANE)
	{
		PhysicsPlane* physicsplane = new PhysicsPlane("Phhysics Plane");
		this->addObject(physicsplane);
	}

}

void GameObjectManager::generatePhysicsCube()
{
	for(int i = 0; i < 20; i++)
	{
		PhysicsCube* physicsCube = new PhysicsCube("Physics Cube");
		this->addObject(physicsCube);
	}
}

void GameObjectManager::createOBJMODEL(Mesh* mesh, String name, Texture* text)
{
	OBJStructure* obj = new OBJStructure(mesh, text, name);

	obj->setPosition(0.0f, 1.0f, 0.0f);
	obj->setScale(2.0f, 2.0f, 2.0f);
	this->addObject(obj);

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

void GameObjectManager::deleteObjectByName(String name)
{
	this->deleteObject(this->GameObjectTable.at(name));
}

void GameObjectManager::setSelectedObject(String name)
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

void GameObjectManager::saveEditStates()
{
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->saveEditState();
	}
}

void GameObjectManager::restoreEditStates()
{
	for (int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->restoreEditState();
	}
}

void GameObjectManager::applyEditorAction(EditorAction* action)
{
	AGameObject* object = this->findObjectByName(action->getOwnerName());
	if (object != NULL) {
		
		object->setLocalMatrix(*action->getStoredMatrix().Matrix);
		object->setPosition(action->getStoredPosition());
		object->setRotation(action->getStoredRotation().x, action->getStoredRotation().y, action->getStoredRotation().z);
		object->setScale(action->getStoredScale());

	}
}

void GameObjectManager::hundreadCubes()
{
	int max = 1.5f;
	int min = -2.5f;
	Math math;
	for (int i = 0; i < 100; i++)
	{
		float x = math.getRandom(min, max);
		float y = math.getRandom(min, max);
		Cube* cube = new Cube("Cube", AGameObject::CUBE);
		cube->setPosition(x, y, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
		
	}

}

void GameObjectManager::createObjectFromFile(String name, AGameObject::PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale, bool rigidBody)
{
	if (type == AGameObject::PrimitiveType::CUBE) {
		Cube* cube = new Cube(name, AGameObject::CUBE);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		if(rigidBody)
		{
			cube->ComputeLocalMatrix();
			cube->attachComponent(new PhysicsComponent("Physics Component", cube));
			
		}
		this->addObject(cube);
	}
	else if(type == AGameObject::PrimitiveType::CAPSULE)
	{
		Capsule* capsule = new Capsule("Capsule");
		capsule->setPosition(position);
		capsule->setRotation(rotation);
		capsule->setScale(scale);
		if (rigidBody)
		{
			capsule->ComputeLocalMatrix();
			capsule->attachComponent(new PhysicsComponent("Physics Component", capsule));
		}
		this->addObject(capsule);
	}

	else if (type == AGameObject::PrimitiveType::PLANE) {
		Plane* plane = new Plane(name);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		if (rigidBody)
		{
			plane->ComputeLocalMatrix();
			plane->attachComponent(new PhysicsComponent("Physics Component", plane));
			PhysicsComponent* component = (PhysicsComponent*)plane->findComponentbyType(AComponent::ComponentType::Physics, "Physics Component");
			//component->getRigidBody()->setType(BodyType::KINEMATIC);
		}
		this->addObject(plane);
	}

	else if (type == AGameObject::PrimitiveType::TEXTURED_CUBE) {
		TexturedCube* texturedcube = new TexturedCube(name);
		texturedcube->setPosition(position);
		texturedcube->setRotation(rotation);
		texturedcube->setScale(scale);
		this->addObject(texturedcube);
	}

	else if (type == AGameObject::PrimitiveType::PHYSICS_CUBE) {
		PhysicsCube* physicscube = new PhysicsCube(name);
		physicscube->setPosition(position);
		physicscube->setRotation(rotation);
		physicscube->setScale(scale);
		this->addObject(physicscube);
	}

	else if (type == AGameObject::PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane(name);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		this->addObject(plane);
	}

	else if(type == AGameObject::PrimitiveType::CYLINDER)
	{
		Cylinder* cylinder = new Cylinder(name);
		cylinder->setPosition(position);
		cylinder->setRotation(rotation);
		cylinder->setScale(scale);
		if (rigidBody)
		{
			cylinder->ComputeLocalMatrix();
			cylinder->attachComponent(new PhysicsComponent("Physics Component", cylinder));
		}
		this->addObject(cylinder);
	}

	else if(type == AGameObject::PrimitiveType::SPHERE)
	{
		Sphere* sphere = new Sphere(name);
		sphere->setPosition(position);
		sphere->setRotation(rotation);
		sphere->setScale(scale);
		if (rigidBody)
		{
			sphere->ComputeLocalMatrix();
			sphere->attachComponent(new PhysicsComponent("Physics Component", sphere));
		}
		this->addObject(sphere);
	}
}


GameObjectManager::~GameObjectManager()
{
	delete this->SelectedObject;
	
}

