#pragma once
#include "AUIScreen.h"
#include "UIManager.h"
#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_dx11.h"
#include "IMGUI\imgui_impl_win32.h"

class ProfilerScreen: public AUIScreen
{
public:
	ProfilerScreen();
	void drawUI() override;
	~ProfilerScreen();
};

