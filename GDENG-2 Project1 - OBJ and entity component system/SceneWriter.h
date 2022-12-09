#pragma once
#include <string>
#include <fstream>
#include "Vector3D.h"

class SceneWriter
{
public:

	typedef std::fstream FileWriter;
	typedef std::string String;

	SceneWriter(String directory);
	void writeCoordinatesToFile(FileWriter file, Vector3D transform);
	void writeToFile();
	~SceneWriter();

private:
	String directory;
};

