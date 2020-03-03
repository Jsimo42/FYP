#include "pch.h"
#include "MainMenu.h"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::Initialise()
{
}

void MainMenu::ShowMenu(bool & bGenerateLevel, int & Layers, std::vector<std::string>& LayerFilePaths, std::unordered_map<EColour, std::string>& ColourMeshKey)
{
	//LayerFilePaths.push_back("Layers/Layer1.txt");
	LayerFilePaths.push_back("Layers/Layer2.txt");
	LayerFilePaths.push_back("Layers/Layer3.txt");
	LayerFilePaths.push_back("Layers/Layer4.txt");
}
