#pragma once
#include "Texture.h"
#include "TextureManager.h"
#include <unordered_map>

class Texture;
class TextureManager;



class TextureFileName
{
public:
	typedef std::wstring String;
	const String WOOD = L"Assets\\Textures\\wood.jpg";
	const String BRICK = L"Assets\\Textures\\brick.png";
	const String WALL = L"Assets\\Textures\\wall.jpg";
};

class TextureLibrary
{
public:
	
	typedef std::wstring String;
	typedef std::unordered_map<String, Texture*> TextureTable;

	static TextureLibrary* getInstance();
	static void initialize();
	static void destroy();

	Texture* getTexture(String textureName);

private:
	TextureLibrary();
	~TextureLibrary();
	TextureLibrary(TextureLibrary const&) {};
	TextureLibrary& operator=(TextureLibrary const&) {};
	static TextureLibrary* sharedInstance;

private:
	TextureTable availableTextures;
};

