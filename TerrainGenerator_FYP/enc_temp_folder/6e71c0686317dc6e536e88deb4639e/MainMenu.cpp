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

void MainMenu::ShowMenu(bool & bGenerateLevel, int & Layers, std::vector<std::string>& LayerFilePaths, std::vector<Agent*> Agents)
{
	LayerFilePaths.push_back("Layers/TestLayer.png");
	//LayerFilePaths.push_back("Layers/Layer2.txt");
	//LayerFilePaths.push_back("Layers/Layer3.txt");
	//LayerFilePaths.push_back("Layers/Layer4.txt");

	Agents.push_back(new Agent(EColour::EWhite, cv::Vec3b(255,255,255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::ERed, cv::Vec3b(0, 0, 255), true, EEntityType::EPyramid));
}
