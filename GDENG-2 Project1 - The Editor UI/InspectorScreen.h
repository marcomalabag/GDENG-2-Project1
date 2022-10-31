#pragma once
#include "UIManager.h"
#include "AUIScreen.h"
#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_dx11.h"
#include "IMGUI\imgui_impl_win32.h"

class InspectorScreen: public AUIScreen
{
public:
	InspectorScreen();
	void drawUI() override;
	~InspectorScreen();
};

