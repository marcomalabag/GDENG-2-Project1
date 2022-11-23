#include "ScreenActions.h"

ScreenActions::ScreenActions() : AUIScreen("Actions")
{
}

void ScreenActions::drawUI()
{
	ImGui::Begin("Actions");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1425, 155));
	ImGui::SetWindowSize(ImVec2(290, UIManager::WINDOW_HEIGHT - 800));
	ImGui::End();
}

ScreenActions::~ScreenActions()
{
	
}

