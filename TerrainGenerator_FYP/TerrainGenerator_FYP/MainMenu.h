#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"


class MainMenu
{
public:
	MainMenu() {};
	~MainMenu();

	void Initialise(GraphicsEngine* Graphics);

	bool ShowMenu(bool& bGenerateGround, std::vector<std::string>& LayerFilePaths, std::vector<Agent*> &Agents, GraphicsEngine* Graphics);
};

