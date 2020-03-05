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

void MainMenu::ShowMenu(bool & bGenerateGround, std::vector<std::string>& LayerFilePaths, std::vector<Agent*> &Agents)
{
	bGenerateGround = true;

	LayerFilePaths.push_back("Layers/Layer.png");
	LayerFilePaths.push_back("Layers/Layer2.png");
	LayerFilePaths.push_back("Layers/Layer3.png");
	//LayerFilePaths.push_back("Layers/Layer4.txt");

	Agents.push_back(new Agent(EColour::EWhite, cv::Vec3b(255,255,255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::ERed, cv::Vec3b(0, 0, 255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EBlue, cv::Vec3b(255, 0, 0), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EGreen, cv::Vec3b(0, 255, 0), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::ELightBlue, cv::Vec3b(255, 255, 0), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EYellow, cv::Vec3b(0, 255, 255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EPink, cv::Vec3b(255, 0, 255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EBlack, cv::Vec3b(0, 0, 0), true, EEntityType::ECube));

	//TODO Setup Model Loading
	//Agents.push_back(new Agent(EColour::ERed, cv::Vec3b(0, 0, 255), false, EEntityType::EModel, "Models/scene.fbx"));
}
