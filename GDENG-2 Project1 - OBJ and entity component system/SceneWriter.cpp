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
	String fileDir = this->directory + ".xml";
	if (this->directory.find(".xml") != String::npos) {
		fileDir = this->directory;
	}

	FileWriter  sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	GameObjectManager::ObjectList List = GameObjectManager::getInstance()->getAllObjects();

	for(AGameObject* gameObject: List)
	{
		
		Vector3D position = gameObject->getLocalPosition();
		Vector3D rotation = gameObject->getLocalRotation();
		Vector3D scale = gameObject->getLocalScale();

		sceneFile << "<GameObject>" << std::endl;
		sceneFile << "<Name>" + gameObject->getName() + "</Name>" << std::endl;
		sceneFile << "<Type>" + std::to_string(gameObject->getType()) + "</Type>" << std::endl;
		sceneFile << "<Position>" << std::endl;
		sceneFile << "<x>" + std::to_string(position.x) + "</x>" << std::endl;
		sceneFile << "<y>" + std::to_string(position.y) + "</y>" << std::endl;
		sceneFile << "<z>" + std::to_string(position.z) + "</z>" << std::endl;
		sceneFile << "</Position>" << std::endl;
		sceneFile << "<Scale>" << std::endl;
		sceneFile << "<x>" + std::to_string(scale.x) + "</x>" << std::endl;
		sceneFile << "<y>" + std::to_string(scale.y) + "</y>" << std::endl;
		sceneFile << "<z>" + std::to_string(scale.z) + "</z>" << std::endl;
		sceneFile << "</Scale>" << std::endl;
		sceneFile << "<Rotation>" << std::endl;
		sceneFile << "<x>" + std::to_string(rotation.x) + "</x>" << std::endl;
		sceneFile << "<y>" + std::to_string(rotation.y) + "</y>" << std::endl;
		sceneFile << "<z>" + std::to_string(rotation.z) + "</z>" << std::endl;
		sceneFile << "</Rotation>" << std::endl;
		sceneFile << "</GameObject>" << std::endl;
	}

	sceneFile.close();
	
}

SceneWriter::~SceneWriter()
{
}
