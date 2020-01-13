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

	void CreateLevel(std::string FileName);
	void Render(GraphicsEngine* Graphics);

private:
	int EntityVector{ 0 };
	std::vector<Entity*> EntityVector;

	int TestLevel[2][2]{ 0, 0, 1, 0 };
};

