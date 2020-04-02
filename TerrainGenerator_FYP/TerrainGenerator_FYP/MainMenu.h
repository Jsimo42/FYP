#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"


class MainMenu
{
public:
	MainMenu() {};
	~MainMenu();

	bool Initialise(const int Width, const int Height, float GLMajorVer, float GLMinorVer);

	bool ShowMenu(bool& bGenerateGround, std::vector<std::string>& LayerFilePaths, std::vector<Agent*> &Agents);

private:
	GLFWwindow* MenuWindow{ nullptr };
	int WindowWidth{ 0 };
	int WindowHeight{ 0 };

	bool InitialiseGLFW(float GLMajorVer, float GLMinorVer);

};

