#include "PhysicsSystem.h"

#include "PhysicsComponent.h"

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings worldSeting;
	worldSeting.defaultVelocitySolverNbIterations = 54;
	worldSeting.gravity = Vector3(0, -9.81, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(worldSeting);
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	this->componentList.push_back(component);
	this->componentTable[component->getName()] = component;
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	this->componentTable.erase(component->getName());
	int index = -1;
	for(int i = 0; i < this->componentList.size(); i++)
	{
		if(this->componentList[i]->getName() == component->getName())
		{
			index = i;
			this->componentList.erase(this->componentList.begin() + index);
			break;
		}
	}
}

PhysicsComponent* PhysicsSystem::findComponentByName(String name)
{
	return this->componentTable.at(name);
}

void PhysicsSystem::updateAllComponents()
{
	this->ticks = EngineTime::getDeltaTime() * 1.0f;
	this->physicsWorld->update(this->ticks);
	for(int i = 0; i < this->componentList.size(); i++)
	{
		this->componentList[i]->perform(this->ticks);
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}

PhysicsSystem::~PhysicsSystem()
{
	this->componentList.clear();
	this->componentTable.clear();
	this->physicsCommon = nullptr;
	this->physicsWorld = nullptr;
}


