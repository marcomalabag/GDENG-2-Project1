#include "TextureLibrary.h"

TextureLibrary* TextureLibrary::sharedInstance = NULL;

TextureLibrary* TextureLibrary::getInstance()
{
	return sharedInstance;
}

void TextureLibrary::initialize()
{
	sharedInstance = new TextureLibrary();
}

void TextureLibrary::destroy()
{
	delete sharedInstance;
}

Texture* TextureLibrary::getTexture(String textureName)
{
	return this->availableTextures.at(textureName);
}

TextureLibrary::TextureLibrary()
{
	TextureFileName filename;
	this->availableTextures[filename.WALL] = TextureManager::getInstance()->createTextureFromFile(filename.WALL.c_str());
	this->availableTextures[filename.BRICK] = TextureManager::getInstance()->createTextureFromFile(filename.BRICK.c_str());
	this->availableTextures[filename.WOOD] = TextureManager::getInstance()->createTextureFromFile(filename.WOOD.c_str());

}

TextureLibrary::~TextureLibrary()
{
}

