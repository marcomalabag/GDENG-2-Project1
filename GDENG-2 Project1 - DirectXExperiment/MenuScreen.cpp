#include "MenuScreen.h"

MenuScreen::MenuScreen():AUIScreen("Menu Screen")
{
	
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { }
			if (ImGui::MenuItem("Save", "Ctrl+S")) {  }
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) { }
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Cube")) {  }
			if (ImGui::MenuItem("Create Sphere")) {  }
			if (ImGui::MenuItem("Create Plane")) {  }
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Color Picker")) {  }
		if (ImGui::BeginMenu("About")) {
			if (ImGui::MenuItem("Credits")) {  }
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Camera"))
		{
			ImGui::EndMenu();
		}
	ImGui::EndMainMenuBar();
	
}

MenuScreen::~MenuScreen()
{
}
