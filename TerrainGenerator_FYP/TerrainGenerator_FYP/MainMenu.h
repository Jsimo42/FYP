#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"

enum EFormCompletion
{
	EDone,
	ENeedsLayers,
	ENeedsModels
};


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

	char EmptyBuffer[64] = "";
	char LastBuffer[64] = "";
	std::string ModelInput = "";
	EFormCompletion FormComplete = EFormCompletion::ENeedsLayers;

	bool InitialiseGLFW(float GLMajorVer, float GLMinorVer);

	void DrawAgentWindow(std::vector<Agent*> &Agents, bool &ShowWindow);
	void DrawModelWindow(std::vector<Agent*> &Agents, bool &ShowWindow);

	void CheckEverythingComplete(std::vector<std::string>& LayerFilePaths, std::vector<Agent*> &Agents);
	void SaveConfig(std::vector<Agent*> &Agents);
	void LoadConfig(std::vector<Agent*> &Agents);
};

