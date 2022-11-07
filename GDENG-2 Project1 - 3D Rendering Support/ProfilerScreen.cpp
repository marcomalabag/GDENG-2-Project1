#include "ProfilerScreen.h"

ProfilerScreen::ProfilerScreen(): AUIScreen("Profile Screen")
{

}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("Engine Profiler");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1425, 550));
	ImGui::SetWindowSize(ImVec2(290, UIManager::WINDOW_HEIGHT - 700));
	ImGui::Text("Application average framerate: %.3f \n Framerate:(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

ProfilerScreen::~ProfilerScreen()
{
}
