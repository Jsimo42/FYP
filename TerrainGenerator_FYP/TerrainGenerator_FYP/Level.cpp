#include "pch.h"
#include "Level.h"


Level::Level(int Layers)
{
}


Level::~Level()
{
	for (int i = 0; i < LayerVector.size(); i++)
	{
		delete LayerVector[i];
	}
}

void Level::CreateLevel(std::vector<std::string> FilePaths)
{
	for (int i = 0; i < FilePaths.size(); i++)
	{
		LayerVector.push_back(CreateLayer(FilePaths[i]));
	}
}

void Level::Render(GraphicsEngine * Graphics)
{
	for (int i = 0; i < LayerCount; i++)
	{
		LayerVector[i]->Render(Graphics);
	}
}

Layer* Level::CreateLayer(std::string FilePath)
{
	return new Layer();
}
