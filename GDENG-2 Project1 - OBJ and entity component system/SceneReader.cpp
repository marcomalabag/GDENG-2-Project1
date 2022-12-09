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
	String objectName;
	AGameObject::PrimitiveType objectType;
	bool rigidBody;
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
			
			position = GetTransformFromXML(GameObjectNode.child("Position"));

			scale = GetTransformFromXML(GameObjectNode.child("Scale"));
			
			rotation = GetTransformFromXML(GameObjectNode.child("Rotation"));

			rigidBody = GameObjectNode.child("RigidBody").child_value();

			GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, rigidBody);
		}
		
	}
}

Vector3D SceneReader::GetTransformFromXML(pugi::xml_node transform)
{
	float x = std::stof(transform.child("x").child_value());
	float y = std::stof(transform.child("y").child_value());
	float z = std::stof(transform.child("z").child_value());
	return Vector3D(x, y, z);
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
