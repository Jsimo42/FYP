#pragma once

#include "Libs.h"
#include "Layer.h"
#include "GraphicsEngine.h"

/* Holds the layers passed in by user */

class Level
{
public:
	Level(int Layers);
	~Level();

	void CreateLevel(std::vector<std::string> FilePaths);

	void Render(GraphicsEngine* Graphics);

private:
	int LayerCount{ 0 };
	std::vector<Layer*> LayerVector;

	Layer* CreateLayer(std::string FilePath);
};

