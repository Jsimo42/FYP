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
	Graphics = new GraphicsEngine("Terrain Generator", 1960, 1080, 4, 4);
	Menu = new MainMenu();
	MainLevel = new Level();

	Graphics->Initialise();
	Menu->Initialise();

	CreateMenu();
	return true;
}

void WorldEngine::CreateMenu()
{
	Menu->ShowMenu(bGenerateGround, LayerCount, LayerFilePaths, ColourMeshKey);
	CreateLevel();
}

bool WorldEngine::CreateLevel()
{
	MainLevel->CreateLevel(LayerFilePaths, Graphics);

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
