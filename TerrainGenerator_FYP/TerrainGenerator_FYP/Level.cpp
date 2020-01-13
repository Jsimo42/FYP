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

void Level::Render(GraphicsEngine * Graphics)
{
	for (int i = 0; i < LayerCount; i++)
	{
		LayerVector[i]->Render(Graphics);
	}
}
