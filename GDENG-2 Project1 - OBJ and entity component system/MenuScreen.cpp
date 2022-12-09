#include "MenuScreen.h"
#include "SceneReader.h"
#include "SceneWriter.h"
#include "UIManager.h"

MenuScreen::MenuScreen():AUIScreen("Menu Screen")
{
	this->openSceneDialog = new ImGui::FileBrowser();
	this->openSceneDialog->SetTitle("Open Scene");
	this->openSceneDialog->SetTypeFilters({ ".xml" });

	this->saveSceneDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	this->saveSceneDialog->SetTitle("Save Scene");
	this->saveSceneDialog->SetTypeFilters({ ".xml" });

	this->objDialog = new ImGui::FileBrowser();
	this->objDialog->SetTitle("Select OBJ");
	this->objDialog->SetTypeFilters({ ".obj" });

	this->textureDialogue = new ImGui::FileBrowser();
	this->textureDialogue->SetTitle("Select Texture");
	this->textureDialogue->SetTypeFilters({ ".jpg", ".png" });
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) {
				this->openSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
				this->saveSceneDialog->Open();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Cube")) { GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE); }
			if (ImGui::MenuItem("Create Textured Cube")) { GameObjectManager::getInstance()->createObject(GameObjectManager::TEXTURED_CUBE); }
			if (ImGui::MenuItem("Create Physics Cube")) { GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PHYSICS_CUBE); }
			if (ImGui::MenuItem("Create Sphere")) { GameObjectManager::getInstance()->createObject(GameObjectManager::SPHERE); }
			if (ImGui::MenuItem("Create Capsule")) { GameObjectManager::getInstance()->createObject(GameObjectManager::CAPSULE); }
			if (ImGui::MenuItem("Create Plane")) { GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE); }
			if (ImGui::MenuItem("Create Physics Plane")) { GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PHYSICS_PLANE); }
			if(ImGui::MenuItem("Create Cylinder")){ GameObjectManager::getInstance()->createObject(GameObjectManager::CYLINDER);}
			if (ImGui::MenuItem("Generate 20 Physics Cubes")) { GameObjectManager::getInstance()->generatePhysicsCube(); }
			if (ImGui::MenuItem("10000 Cubes")) { GameObjectManager::getInstance()->hundreadCubes(); }
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu("OBJ Model"))
		{
			if (ImGui::MenuItem("Select OBJ Model")) { this->objDialog->Open(); }
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Color Picker")) { UIManager::getInstance()->showColorPickerScreen(); }
		if (ImGui::BeginMenu("About")) {
			if (ImGui::MenuItem("Credits")) { UIManager::getInstance()->showCreditsScreen(); }
			ImGui::EndMenu();
		}

		this->openSceneDialog->Display();
		this->saveSceneDialog->Display();
		this->objDialog->Display();
		this->textureDialogue->Display();

		if (this->saveSceneDialog->HasSelected())
		{
			SceneWriter writer = SceneWriter(this->saveSceneDialog->GetSelected().string());
			writer.writeToFile();

			this->saveSceneDialog->ClearSelected();
			this->saveSceneDialog->Close();
		}

		else if (this->openSceneDialog->HasSelected()) {
			SceneReader reader = SceneReader(this->openSceneDialog->GetSelected().string());
			reader.readFromFile();

			this->openSceneDialog->ClearSelected();
			this->openSceneDialog->Close();
		}

		else if(this->objDialog->HasSelected())
		{
			
			this->mesh = MeshManager::getInstance()->createMeshFromFile(this->objDialog->GetSelected().c_str());
			
			this->OBJname = this->objDialog->GetSelected().string().substr(this->objDialog->GetSelected().string().find("Meshes\\"));
			this->OBJname = this->OBJname.substr(this->OBJname.find("\\"));
			this->OBJname.erase(this->OBJname.begin() + this->OBJname.find("\\"));
			this->OBJname.erase(this->OBJname.find(".obj"));

			this->objDialog->ClearSelected();
			this->objDialog->Close();

			this->textureDialogue->Open();


		}

		else if (this->textureDialogue->HasSelected())
		{
			text = TextureManager::getInstance()->createTextureFromFile(this->textureDialogue->GetSelected().c_str());
			this->textureDialogue->ClearSelected();
			this->textureDialogue->Close();

			GameObjectManager::getInstance()->createOBJMODEL(this->mesh, this->OBJname, this->text);
		}

		ImGui::EndMainMenuBar();
	}
}

MenuScreen::~MenuScreen()
{
}
