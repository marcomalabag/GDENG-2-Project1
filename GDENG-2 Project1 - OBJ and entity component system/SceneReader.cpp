#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"


typedef std::fstream FileReader;

SceneReader::SceneReader(String directory)
{
	this->directory = directory;
}

void SceneReader::readFromFile()
{
	String fileDir = this->directory + ".iet";
	if (this->directory.find(".iet") != String::npos) {
		fileDir = this->directory;
	}

	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	String readLine;

	String objectName;
	AGameObject::PrimitiveType objectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	while (std::getline(sceneFile, readLine)) {
		if (index == 0) {
			objectName = readLine;
			index++;
		}
		else if (index == 1) {
			
			std::vector stringSplit = this->split(readLine, ' ');
			objectType = (AGameObject::PrimitiveType)std::stoi(stringSplit[1]);
			index++;
		}
		else if (index == 2) {
			std::vector stringSplit = this->split(readLine, ' ');
			position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 3) {
			std::vector stringSplit = this->split(readLine, ' ');
			scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 4) {
			std::vector stringSplit = this->split(readLine, ' ');
			rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index = 0;

			GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale);
		}
	}
}

std::vector<std::string> SceneReader::split(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}

	return elems;
}

SceneReader::~SceneReader()
{
}
