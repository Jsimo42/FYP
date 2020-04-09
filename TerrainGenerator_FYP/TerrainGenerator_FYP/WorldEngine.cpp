#include "pch.h"
#include "WorldEngine.h"


WorldEngine::WorldEngine()
{
}


WorldEngine::~WorldEngine()
{
}

bool WorldEngine::Initialise()
{
	Graphics = new GraphicsEngine("Terrain Generator", 1960, 1080, 4, 3);
	Menu = new MainMenu();
	MainLevel = new Level();

	Menu->Initialise(735, 685, 4, 3);

	CreateMenu();
	return true;
}

void WorldEngine::CreateMenu()
{
	Menu->ShowMenu(bGenerateGround, LayerFilePaths, Agents);

	Graphics->Initialise();
	CreateLevel();
}

bool WorldEngine::CreateLevel()
{
	MainLevel->CreateLevel(bGenerateGround, LayerFilePaths, Graphics, Agents);

	return true;
}

void WorldEngine::Run()
{
	while (Graphics->GetWindowShouldClose() == false)
	{
		Update();
		Render();
	}
}

void WorldEngine::Update()
{
	Graphics->Update();
}

void WorldEngine::Render()
{
	MainLevel->Render(Graphics);
}
