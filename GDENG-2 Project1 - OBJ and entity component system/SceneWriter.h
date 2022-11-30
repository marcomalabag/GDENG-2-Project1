#pragma once
#include <string>

class SceneWriter
{
public:
	typedef std::string String;
	SceneWriter(String directory);
	void writeToFile();
	~SceneWriter();

private:
	String directory;
};

