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

	void Render(GraphicsEngine* Graphics);

private:
	int LayerCount{ 0 };
	std::vector<Layer*> LayerVector;
};

