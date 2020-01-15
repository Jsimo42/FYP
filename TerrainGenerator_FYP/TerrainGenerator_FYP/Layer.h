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

	std::vector<Entity*> GetEntities() { return EntityVector; };

private:
	int EntityCount{ 0 };
	std::vector<Entity*> EntityVector;

	int TestLevel[8][2]{ 0, 0, 1, 0 ,  0, 0, 1, 0 , 0, 0, 1, 0 , 0, 0, 1, 0};
};

