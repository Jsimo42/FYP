#pragma once

#include "Libs.h"
#include "Entity.h"
#include "GraphicsEngine.h"

/* Creates the level using Entities */

class Layer
{
public:
	Layer();
	~Layer();

	void CreateLayer(std::string FileName, GraphicsEngine* Graphics);
	void Render(GraphicsEngine* Graphics);

private:
	int EntityCount{ 0 };
	std::vector<Entity*> EntityVector;

	int TestLevel[2][2]{ 0, 0, 1, 0 };
};

