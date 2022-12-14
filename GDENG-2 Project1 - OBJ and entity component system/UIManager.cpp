#include "UIManager.h"
#include <iostream>

UIManager* UIManager::sharedInstance = NULL;


UIManager::UIManager(HWND windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getD3Ddevice(), GraphicsEngine::getInstance()->getImmediateDeviceContext()->getContext());

	UINames uiNames;
	ProfilerScreen* profilerScreen = new ProfilerScreen();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uiList.push_back(profilerScreen);

	MenuScreen* menuScreen = new MenuScreen();
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);

	InspectorScreen* inspectorScreen = new InspectorScreen();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);

	HierarchyScreen* hierarchyScreen = new HierarchyScreen();
	this->uiTable[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
	this->uiList.push_back(hierarchyScreen);

	CreditsScreen* creditsScreen = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);

	ColorPickerScreen* colorPickerScreen = new ColorPickerScreen();
	this->uiTable[uiNames.COLORPICKER_SCREEN] = colorPickerScreen;
	this->uiList.push_back(colorPickerScreen);

	ScreenPlayBack* playBackScreen = new ScreenPlayBack();
	this->uiTable[uiNames.PLAYBACK_SCREEN] = playBackScreen;
	this->uiList.push_back(playBackScreen);

	ScreenActions* ActionsScreen = new ScreenActions();
	this->uiTable[uiNames.ACTIONS_SCREEN] = ActionsScreen;
	this->uiList.push_back(ActionsScreen);

	DebugConsoleScreen* debugConsoleScreen = new DebugConsoleScreen();
	this->uiTable[uiNames.DEBUG_CONSOLE_SCREEN] = debugConsoleScreen;
	this->uiList.push_back(debugConsoleScreen);
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	UINames uiNames;

	for(int i = 0; i < uiList.size(); i++){
		if(this->uiList[i]->getName() == "Credits Screen" && !showCredits)
		{
			continue;
		}
		else if(this->uiList[i]->getName() == "Color Picker" && !showColorPicker)
		{
			continue;
		}
		else
		{
			this->uiList[i]->drawUI();
		}
		
	}

	//ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::hideCreditsScreen()
{
	showCredits = false;
}

void UIManager::showCreditsScreen()
{
	showCredits = true;
}

void UIManager::hideColorPickerScreen()
{
	this->showColorPicker = false;
}

void UIManager::showColorPickerScreen()
{
	this->showColorPicker = true;
}

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}


UIManager::~UIManager()
{
}


