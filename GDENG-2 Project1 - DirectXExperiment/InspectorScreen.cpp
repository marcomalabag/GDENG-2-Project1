#include "InspectorScreen.h"

InspectorScreen::InspectorScreen():AUIScreen("Inspector Screen")
{
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector Window");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 275, 25));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
	ImGui::End();
}

InspectorScreen::~InspectorScreen()
{
}
