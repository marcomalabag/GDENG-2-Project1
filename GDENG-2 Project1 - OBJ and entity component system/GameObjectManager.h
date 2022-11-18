#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "AGameObject.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "PhysicsCube.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Sphere.h"
#include "TexturedCube.h"
#include "OBJStructure.h"
#include "TextureLibrary.h"
#include "MeshManager.h"

typedef std::string String;
typedef std::vector<AGameObject*> ObjectList;
typedef std::unordered_map<String, AGameObject*> HashTable;

class GameObjectManager
{
public:
	

	enum PrimitiveType
	{
		CUBE,
		PLANE,
		SPHERE,
		CYLINDER,
		TEXTURED_CUBE,
		PHYSICS_CUBE
	};

	enum OBJMODEL
	{	
		TEAPOT,
		ARMADILLO,
		BUNNY,
		STATUE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(String name);
	ObjectList getAllObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	void createOBJMODEL(OBJMODEL model);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(String name);
	void setSelectedObject(String name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();
	
private:
	static GameObjectManager* sharedInstance;

	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	AGameObject* SelectedObject;
	ObjectList GameObjectList;
	HashTable GameObjectTable;

	int cubeCounter = 0;
	int sphereCounter = 0;
	int cylinderCounter = 0;
	int planeCounter = 0;
	int TexturedCubecounter = 0;
};

