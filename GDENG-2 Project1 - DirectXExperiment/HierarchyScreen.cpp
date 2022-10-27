#include "HierarchyScreen.h"

HierarchyScreen::HierarchyScreen():AUIScreen("HierarchyScreen")
{
}

void HierarchyScreen::drawUI()
{
	ImGui::Begin("Scene Outliner");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 325, 25));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));

	ImGui::End();
}


