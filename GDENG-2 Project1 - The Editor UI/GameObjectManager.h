#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "AGameObject.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Sphere.h"
#include "Card.h"

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
		CARD
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(string name);
	ObjectList getAllObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(string name);
	void setSelectedObject(string name);
	void setSelectedObject(AGameObject* gameObject);
	void hundreadCubes();
	void fiftyCubes();
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
};

