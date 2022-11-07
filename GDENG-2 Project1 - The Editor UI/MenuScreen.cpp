#include "MenuScreen.h"

#include "UIManager.h"

MenuScreen::MenuScreen():AUIScreen("Menu Screen")
{
	
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Cube")) { GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE); }
			if (ImGui::MenuItem("Create Textured Cube")) { /*Do something */ }
			if (ImGui::MenuItem("Create Sphere")) { GameObjectManager::getInstance()->createObject(GameObjectManager::SPHERE); }
			if (ImGui::MenuItem("Create Plane")) { GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE); }
			if(ImGui::MenuItem("Create Cylinder")){ GameObjectManager::getInstance()->createObject(GameObjectManager::CYLINDER);}
			if (ImGui::MenuItem("50 Cubes")) { GameObjectManager::getInstance()->fiftyCubes(); }
			if (ImGui::MenuItem("Create Card")) { GameObjectManager::getInstance()->createObject(GameObjectManager::CARD); }
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Color Picker")) { UIManager::getInstance()->showColorPickerScreen(); }
		if (ImGui::BeginMenu("About")) {
			if (ImGui::MenuItem("Credits")) { UIManager::getInstance()->showCreditsScreen(); }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

MenuScreen::~MenuScreen()
{
}
