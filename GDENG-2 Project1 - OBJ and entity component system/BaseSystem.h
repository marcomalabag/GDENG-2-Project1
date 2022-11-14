#pragma once
#include "PhysicsSystem.h"

class PhysicsSystem;
class BaseSystem
{
public:
	typedef std::string String;

	static BaseSystem* getInstance();
	static void initialize();
	static void destroy();

	PhysicsSystem* getPhysicsSystem();

private:
	BaseSystem();
	~BaseSystem();
	BaseSystem(BaseSystem const&) {};
	BaseSystem& operator=(BaseSystem const&) {};
	static BaseSystem* sharedInstance;

	PhysicsSystem* physicsSystem;
};

