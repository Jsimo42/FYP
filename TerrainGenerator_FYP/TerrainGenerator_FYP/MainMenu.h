#pragma once

#include "Libs.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void Initialise();

	void ShowMenu(bool& bGenerateLevel, int& Layers, std::vector<std::string>& LayerFilePaths, std::unordered_map<EColour, std::string>& ColourMeshKey);
};
