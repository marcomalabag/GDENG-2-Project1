#include "CreditsScreen.h"

CreditsScreen::CreditsScreen():AUIScreen("Credits Screen")
{
}

void CreditsScreen::drawUI()
{
	ImGuiStyle& style = ImGui::GetStyle();


	if(ImGui::Begin("Credits"))
	{
		
		float width = ImGui::GetWindowSize().x;
		float centre_position_for_button = (width - ImVec2(70.0f, 0.0f).x) / 2;
		ImGui::SetCursorPosX(centre_position_for_button);

		ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1125, 25));
		ImGui::SetWindowSize(ImVec2(550, UIManager::WINDOW_HEIGHT - 550));
		ImGui::Text("About:\n");
		ImGui::Text("Scene Editor v0.01\n");
		ImGui::Text("Developer: Marco Malabag\n");
		ImGui::Text("Acknowledgement: Most of the code is gotten from \npardcode and sir Neil Gallego.\nThe ImGui API is from 'https://github.com/ocornut/imgui'");


		if (ImGui::Button("Close", ImVec2(70.0f, 0.0f)))
		{

			UIManager::getInstance()->hideCreditsScreen();
		}

	}

	
	ImGui::End();
}

CreditsScreen::~CreditsScreen()
{
}


