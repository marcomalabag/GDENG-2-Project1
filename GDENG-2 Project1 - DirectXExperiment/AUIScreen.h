#pragma once
#include <iostream>
#include "UIManager.h"
typedef std::string String;



class AUIScreen
{
protected:
	typedef std::string String;

	AUIScreen(String name);
	~AUIScreen();

	String getName();
	virtual void drawUI() = 0;

	String name;

	friend class UIManager;
};

