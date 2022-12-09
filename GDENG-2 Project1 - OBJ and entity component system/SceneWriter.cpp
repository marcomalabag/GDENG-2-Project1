#include "SceneWriter.h"
#include <iostream>
#include "AComponent.h"
#include "GameObjectManager.h"
#include "pugixml-1.13/src/pugixml.hpp"
#include "pugixml-1.13/src/pugiconfig.hpp"


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
	
	sceneFile << "<GameObjects>" << std::endl;
	for(AGameObject* gameObject: List)
	{
		
		Vector3D position = gameObject->getLocalPosition();
		Vector3D rotation = gameObject->getLocalRotation();
		Vector3D scale = gameObject->getLocalScale();

		bool hasRigidBody = gameObject->findComponentbyType(AComponent::Physics, "Physics Component");
		if(!hasRigidBody)
		{
			hasRigidBody = false;
		}
		else
		{
			hasRigidBody = true;
		}


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
		sceneFile << "<RigidBody>" + std::to_string(hasRigidBody) + "</RigidBody>" << std::endl;
		sceneFile << "</GameObject>" << std::endl;
	}
	sceneFile << "</GameObjects>" << std::endl;
	sceneFile.close();
	
}

SceneWriter::~SceneWriter()
{
}
