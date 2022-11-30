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
#include "PhysicsPlane.h"
#include "TexturedCube.h"
#include "OBJStructure.h"
#include "MeshManager.h"
#include "EditorAction.h"



class EditorAction;
class GameObjectManager
{
public:

	typedef std::string String;
	typedef std::vector<AGameObject*> ObjectList;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	enum PrimitiveType
	{
		CUBE,
		PLANE,
		SPHERE,
		CYLINDER,
		TEXTURED_CUBE,
		PHYSICS_CUBE,
		PHYSICS_PLANE
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
	void generatePhysicsCube();
	void createOBJMODEL(Mesh* mesh, String name, Texture* text);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(String name);
	void setSelectedObject(String name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();
	void saveEditStates();
	void restoreEditStates();
	void applyEditorAction(EditorAction* action);

	void createObjectFromFile(String name, AGameObject::PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale);
	
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
	int PhysicsPlaneCounter = 0;
	int PhysicsCubeCounter = 0;
};

