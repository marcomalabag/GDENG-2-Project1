#include "SceneWriter.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"

typedef std::fstream FileWriter;

SceneWriter::SceneWriter(String directory)
{
	this->directory = directory;
}

void SceneWriter::writeToFile()
{
	String fileDir = this->directory + ".iet";
	if (this->directory.find(".iet") != String::npos) {
		fileDir = this->directory;
	}

	FileWriter  sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	GameObjectManager::ObjectList List = GameObjectManager::getInstance()->getAllObjects();

	for(AGameObject* gameObject: List)
	{
		sceneFile << gameObject->getName() << std::endl;
		Vector3D position = gameObject->getLocalPosition();
		Vector3D rotation = gameObject->getLocalRotation();
		Vector3D scale = gameObject->getLocalScale();

		sceneFile << "Type: " << gameObject->getType() << std::endl;
		sceneFile << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
		sceneFile << "Scale: " << scale.x << " " << scale.y << " " << scale.z << std::endl;
		sceneFile << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
	}

	sceneFile.close();
	
}

SceneWriter::~SceneWriter()
{
}
