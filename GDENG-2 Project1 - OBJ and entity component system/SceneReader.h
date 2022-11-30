#pragma once
#include <string>
#include <sstream>
#include <vector>

class SceneReader
{
public:
	typedef std::string String;
	SceneReader(String directory);
	void readFromFile();
	std::vector<std::string> split(const std::string& s, char delim);
	~SceneReader();

private:
	String directory;
};

