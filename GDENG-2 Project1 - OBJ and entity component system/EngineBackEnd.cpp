#include "EngineBackEnd.h"
#include <cstddef>

EngineBackEnd* EngineBackEnd::sharedInstance = NULL;


EngineBackEnd::EngineBackEnd()
{
	
}

EngineBackEnd* EngineBackEnd::getInstance()
{
	return sharedInstance;
}

void EngineBackEnd::initialize()
{
	sharedInstance = new EngineBackEnd();
}

void EngineBackEnd::setMode(EditorMode mode)
{
	this->editorMode = mode;
	if(this->editorMode == EditorMode::PLAY)
	{
		
	}
	else if(this->editorMode == EditorMode::EDITOR)
	{
		
	}
}

void EngineBackEnd::startFrameStep()
{
	this->frameStepping = true;
}

void EngineBackEnd::endFrameStep()
{
	this->frameStepping = false;
}

bool EngineBackEnd::insideFrameStep()
{
	return this->frameStepping;
}

EngineBackEnd::EditorMode EngineBackEnd::getMode()
{
	return this->editorMode;
}

void EngineBackEnd::destroy()
{
	delete sharedInstance;
}

EngineBackEnd::~EngineBackEnd()
{
}


