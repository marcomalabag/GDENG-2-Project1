#include "ColorPickerScreen.h"

ColorPickerScreen::ColorPickerScreen(): AUIScreen("Color Picker")
{
	
}

void ColorPickerScreen::drawUI()
{
	float clear_color[] = { 2.0f, 0.3f, 0.4f, 1.0f };

	ImGui::Begin("Color Picker UI");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 1125, 400));
	ImGui::SetWindowSize(ImVec2(210, UIManager::WINDOW_HEIGHT - 587));
	ImGui::ColorEdit4("MyColors", clear_color);
	float width = ImGui::GetWindowSize().x;
	float centre_position_for_button = (width - ImVec2(70.0f, 0.0f).x) / 2;
	ImGui::SetCursorPosX(centre_position_for_button);
	if (ImGui::Button("Close", ImVec2(70.0f, 0.0f)))
	{

		UIManager::getInstance()->hideColorPickerScreen();
	}
	ImGui::End();
}


ColorPickerScreen::~ColorPickerScreen()
{
}
