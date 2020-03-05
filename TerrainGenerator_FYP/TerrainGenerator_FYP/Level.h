#pragma once

#include "Libs.h"
#include "Layer.h"
#include "GraphicsEngine.h"

/* Holds the layers passed in by user */

class Level
{
public:
	Level();
	~Level();

	void CreateLevel(bool GenerateGround, std::vector<std::string> FilePaths, GraphicsEngine* Graphics, std::vector<Agent*> Agents);

	void Render(GraphicsEngine* Graphics);

private:
	int LayerCount{ 1 };
	std::vector<Layer*> LayerVector;

	Layer* CreateLayer(bool GenerateGround, std::string FilePath, GraphicsEngine* Graphics, int LayerNum, std::vector<Agent*> Agents);
};

