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

void Level::CreateLevel(std::vector<std::string> FilePaths, GraphicsEngine* Graphics)
{
	for (int i = 0; i < FilePaths.size(); i++)
	{
		LayerVector.push_back(CreateLayer(FilePaths[i], Graphics));
	}
}

void Level::Render(GraphicsEngine * Graphics)
{
	for (int i = 0; i < LayerVector.size(); i++)
	{
		LayerVector[i]->Render(Graphics);
	}
}

Layer* Level::CreateLayer(std::string FilePath, GraphicsEngine* Graphics)
{
	Layer* NewLayer = new Layer();

	NewLayer->CreateLayer(FilePath, Graphics);

	return NewLayer;
}
