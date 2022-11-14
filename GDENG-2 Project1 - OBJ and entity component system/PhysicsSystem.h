#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsSystem
{
public:
	typedef std::string String;
	//typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;

	PhysicsSystem();
	~PhysicsSystem();
};

