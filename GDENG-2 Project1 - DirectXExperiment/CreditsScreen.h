#pragma once
#include "AUIScreen.h"
#include "UIManager.h"
#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_dx11.h"
#include "IMGUI\imgui_impl_win32.h"

class CreditsScreen: public AUIScreen
{
public:
	CreditsScreen();
	void drawUI() override;
	~CreditsScreen();
};

