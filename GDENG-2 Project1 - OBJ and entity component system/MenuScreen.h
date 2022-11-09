#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include <iostream>

class MenuScreen: public AUIScreen
{
public:
	MenuScreen();
	void drawUI() override;

	void createCubeOnClick();
	~MenuScreen();
};

