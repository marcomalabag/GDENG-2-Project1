#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>
#include "EngineTime.h"

using namespace reactphysics3d;

class PhysicsComponent;
class PhysicsSystem
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
	typedef std::vector <PhysicsComponent*> ComponentList;

	PhysicsSystem();
	~PhysicsSystem();

	void registerComponent(PhysicsComponent* component);
	void unregisterComponent(PhysicsComponent* component);
	PhysicsComponent* findComponentByName(String name);

	void updateAllComponents();
	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

private:
	ComponentTable componentTable;
	ComponentList componentList;

	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;
	float ticks = 0.0f;
};

