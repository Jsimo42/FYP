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

	Graphics->Initialise();
	return true;
}

void WorldEngine::CreateMenu()
{
}

bool WorldEngine::CreateLevel(string FilePath, int Layer)
{
	MainLevel = new Level();

	std::vector<std::string> FilePathVector;
	FilePathVector.push_back("Layers/Layer1.txt");
	FilePathVector.push_back("Layers/Layer2.txt");

	MainLevel->CreateLevel(FilePathVector, Graphics);

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
