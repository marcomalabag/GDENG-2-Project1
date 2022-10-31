#include "ProfilerScreen.h"

ProfilerScreen::ProfilerScreen(): AUIScreen("Profile Screen")
{

}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("Engine Profiler");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1425, 25));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT - 550));
	ImGui::End();
}

ProfilerScreen::~ProfilerScreen()
{
}
