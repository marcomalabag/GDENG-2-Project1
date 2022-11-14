#include "BaseSystem.h"

BaseSystem* BaseSystem::sharedInstance = NULL;

BaseSystem::BaseSystem()
{
	this->physicsSystem = new PhysicsSystem();
}

BaseSystem* BaseSystem::getInstance()
{
	return sharedInstance;
}

void BaseSystem::initialize()
{
	sharedInstance = new BaseSystem();
}

void BaseSystem::destroy()
{
	delete sharedInstance;
}

PhysicsSystem* BaseSystem::getPhysicsSystem()
{
	return this->physicsSystem;
}

BaseSystem::~BaseSystem()
{
}
