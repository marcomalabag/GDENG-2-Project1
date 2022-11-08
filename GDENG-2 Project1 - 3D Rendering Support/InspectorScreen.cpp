#include "InspectorScreen.h"

InspectorScreen::InspectorScreen():AUIScreen("Inspector Screen")
{
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector Window");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 275, 25));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
	this->generateEditor();
	ImGui::End();
}

void InspectorScreen::generateEditor()
{
	if(GameObjectManager::getInstance()->getSelectedObject() != NULL)
	{
		if(GameObjectManager::getInstance()->getSelectedObject()->textureFlag())
		{
			ImGui::Text("Textured Object");
			static const char* textures[] = { "Select Texture", "Brick", "Wall", "Wood"};
			static int currView = 0;

			ImGui::Combo("Current texture", &currView, textures, IM_ARRAYSIZE(textures));
			if(currView == 0)
			{
				GameObjectManager::getInstance()->getSelectedObject()->setObjectTexture(
					GameObjectManager::getInstance()->getSelectedObject()->getObjectTexture());
			}
			else if (currView == 1)
			{
				GameObjectManager::getInstance()->getSelectedObject()->setObjectTexture(
					TextureLibrary::getInstance()->getTexture(filenames.BRICK));
			}
			else if(currView == 2)
			{
				GameObjectManager::getInstance()->getSelectedObject()->setObjectTexture(
					TextureLibrary::getInstance()->getTexture(filenames.WALL));
			}
			else if (currView == 3)
			{
				GameObjectManager::getInstance()->getSelectedObject()->setObjectTexture(
					TextureLibrary::getInstance()->getTexture(filenames.WOOD));
			}
		}


		ImGui::Text("Selected Object: %s", GameObjectManager::getInstance()->getSelectedObject()->getName().c_str());
		this->TransformUpdate();
		if(ImGui::InputFloat3("Position", this->SelectedObjectposition, 3))
		{
			this->TransformSelected(GameObjectManager::getInstance()->getSelectedObject());
		}
		if (ImGui::InputFloat3("Rotation", this->SelectedObjectRotation, 3))
		{
			this->TransformSelected(GameObjectManager::getInstance()->getSelectedObject());
		}
		if (ImGui::InputFloat3("Scale", this->SelectedObjectScale, 3))
		{
			this->TransformSelected(GameObjectManager::getInstance()->getSelectedObject());
		}
		if (ImGui::Button("Delete", ImVec2(70.0f, 0.0f)))
		{
			GameObjectManager::getInstance()->deleteObjectByName(GameObjectManager::getInstance()->getSelectedObject()->getName());
			GameObjectManager::getInstance()->setSelectedObject(NULL);
		}
	}
	else {
		ImGui::Text("No object selected");
	}
	
}

void InspectorScreen::TransformUpdate()
{
	Vector3D position = GameObjectManager::getInstance()->getSelectedObject()->getLocalPosition();
	this->SelectedObjectposition[0] = position.x;
	this->SelectedObjectposition[1] = position.y;
	this->SelectedObjectposition[2] = position.z;

	Vector3D scale = GameObjectManager::getInstance()->getSelectedObject()->getLocalScale();
	this->SelectedObjectScale[0] = scale.x;
	this->SelectedObjectScale[1] = scale.y;
	this->SelectedObjectScale[2] = scale.z;

	Vector3D rotaion = GameObjectManager::getInstance()->getSelectedObject()->getLocalRotation();
	this->SelectedObjectRotation[0] = rotaion.x;
	this->SelectedObjectRotation[1] = rotaion.y;
	this->SelectedObjectRotation[2] = rotaion.z;
}

void InspectorScreen::TransformSelected(AGameObject* selected)
{
	selected->setPosition(this->SelectedObjectposition[0], this->SelectedObjectposition[1], this->SelectedObjectposition[2]);
	selected->setRotation(this->SelectedObjectRotation[0], this->SelectedObjectRotation[1], this->SelectedObjectRotation[2]);
	selected->setScale(this->SelectedObjectScale[0], this->SelectedObjectScale[1], this->SelectedObjectScale[2]);
}

InspectorScreen::~InspectorScreen()
{
}
