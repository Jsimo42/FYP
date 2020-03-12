#pragma once

#include "Libs.h"



class MainMenu
{
public:
	MainMenu() {};
	~MainMenu();

	void Initialise();

	bool ShowMenu(bool& bGenerateGround, std::vector<std::string>& LayerFilePaths, std::vector<Agent*> &Agents);
};

