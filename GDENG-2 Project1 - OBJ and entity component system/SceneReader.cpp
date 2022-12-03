#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"
#include "tinyxml/tinyxml.h"
#include "pugixml-1.13/src/pugixml.hpp"
#include "pugixml-1.13/src/pugiconfig.hpp"


typedef std::fstream FileReader;

SceneReader::SceneReader(String directory)
{
	this->directory = directory;
}

void SceneReader::readFromFile()
{
	String objectName;
	AGameObject::PrimitiveType objectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	String fileDir = this->directory + ".xml";
	if (this->directory.find(".xml") != String::npos) {
		fileDir = this->directory;

	}
	
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileDir.c_str());
	if (!result)
	{
		std::cout << "Parse error: " << result.description()
			<< ", character pos= " << result.offset;
	}
	// A valid XML document must have a single root node
	pugi::xml_node root = doc.first_child();
	
	for(; root; root = root.next_sibling())
	{
		pugi::xml_node GameObjectNode = root.child("GameObject");
		for(; GameObjectNode; GameObjectNode = GameObjectNode.next_sibling())
		{
			String objectName = GameObjectNode.child("Name").child_value();

			objectType = (AGameObject::PrimitiveType)std::stoi(GameObjectNode.child("Type").child_value());

			pugi::xml_node positionNode = GameObjectNode.child("Position");
			float PositionX = std::stof(positionNode.child("x").child_value());
			float PositionY = std::stof(positionNode.child("y").child_value());
			float PositionZ = std::stof(positionNode.child("z").child_value());
			position = Vector3D(PositionX, PositionY, PositionZ);


			pugi::xml_node ScaleNode = GameObjectNode.child("Scale");
			float ScaleX = std::stof(ScaleNode.child("x").child_value());
			float ScaleY = std::stof(ScaleNode.child("y").child_value());
			float ScaleZ = std::stof(ScaleNode.child("z").child_value());
			scale = Vector3D(ScaleX, ScaleY, ScaleZ);


			pugi::xml_node RotationNode = GameObjectNode.child("Rotation");
			float RotationX = std::stof(RotationNode.child("x").child_value());
			float RotationY = std::stof(RotationNode.child("y").child_value());
			float RotationZ = std::stof(RotationNode.child("z").child_value());
			rotation = Vector3D(RotationX, RotationY, RotationZ);

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
