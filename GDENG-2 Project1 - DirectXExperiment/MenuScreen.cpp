#include "MenuScreen.h"

#include "UIManager.h"

MenuScreen::MenuScreen():AUIScreen("Menu Screen")
{
	
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W")) {/*Do something */ }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Cube")) { /*Do something*/ }
			if (ImGui::MenuItem("Create Textured Cube")) { /*Do something */ }
			if (ImGui::MenuItem("Create Sphere")) { /* Do stuff */ }
			if (ImGui::MenuItem("Create Plane")) {
				if (ImGui::MenuItem("Create Cube")) { /*Do something*/ }}
			if (ImGui::MenuItem("Create Bunny")) { /*Do something*/ }
			if (ImGui::MenuItem("Create Statue")) { /*Do something*/ }
			if (ImGui::MenuItem("Create Teapot")) { /*Do something*/ }
			if (ImGui::MenuItem("Create Physics_Cube")) { /*Do something*/ }
			if (ImGui::BeginMenu("Light")) {
				if (ImGui::MenuItem("Point Light")) { /* Do stuff */ }
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Color Picker")) { /*Do something*/ }
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
