#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"
#include "MainMenu.h"
#include "Level.h"

/* Runs Setup and main update loop */

using namespace std;

class WorldEngine
{
public:
	WorldEngine();
	~WorldEngine();

	bool Initialise();

	void CreateMenu();

	bool CreateLevel();

	void Run();

	void Update();
	void Render();

private:
	GraphicsEngine* Graphics{ nullptr };
	MainMenu* Menu{ nullptr };
	Level* MainLevel{ nullptr };

	std::vector<Model*> ModelVector;
	std::vector<Mesh*> MeshVector;

	bool bGenerateGround{ false };
	int LayerCount{ 0 };
	std::vector<std::string> LayerFilePaths;
	std::vector<Agent*> Agents;

	int i = 0;
};

