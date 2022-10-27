#include "ProfilerScreen.h"

ProfilerScreen::ProfilerScreen(): AUIScreen("Profile Screen")
{

}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("Engine Profiler");
	
	ImGui::End();
}

ProfilerScreen::~ProfilerScreen()
{
}
