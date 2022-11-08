#include "TextureLibrary.h"

TextureLibrary* TextureLibrary::sharedInstance = NULL;

void TextureLibrary::initialize()
{
	sharedInstance = new TextureLibrary();
}

TextureLibrary::TextureLibrary()
{
	TextureFileName filename;
	this->availableTextures[filename.WALL] = TextureManager::getInstance()->createTextureFromFile(filename.WALL.c_str());
	this->availableTextures[filename.BRICK] = TextureManager::getInstance()->createTextureFromFile(filename.BRICK.c_str());
	this->availableTextures[filename.WOOD] = TextureManager::getInstance()->createTextureFromFile(filename.WOOD.c_str());

}

