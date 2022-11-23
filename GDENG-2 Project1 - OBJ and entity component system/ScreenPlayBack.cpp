#include "ScreenPlayBack.h"

ScreenPlayBack::ScreenPlayBack(): AUIScreen("Screen Play Back")
{
}

void ScreenPlayBack::drawUI()
{
	ImGui::Begin("Screen Play Back");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1425, 25));
	ImGui::SetWindowSize(ImVec2(290, UIManager::WINDOW_HEIGHT - 800));
	ImGui::End();
}

ScreenPlayBack::~ScreenPlayBack()
{
}
