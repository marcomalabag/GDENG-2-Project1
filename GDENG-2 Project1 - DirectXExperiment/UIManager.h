#pragma once
#include "AUIScreen.h"
#include "UINames.h"
#include "GraphicsEngine.h"
#include "ProfilerScreen.h"
#include "MenuScreen.h"
#include "InspectorScreen.h"
#include "HierarchyScreen.h"
#include "CreditsScreen.h"


class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();
	void hideCreditsScreen();
	void showCreditsScreen();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&){};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
	bool showCredits = false;

};

