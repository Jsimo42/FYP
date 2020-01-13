#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"
#include "Level.h"

/* Runs Setup and main update loop */

using namespace std;

class WorldEngine
{
public:
	WorldEngine();
	~WorldEngine();

	bool CreateLevel(string FilePath, int Layer);
	void Render();


private:
	GraphicsEngine* Graphics = nullptr;

	std::vector<Model*> ModelVector;
	std::vector<Mesh*> MeshVector;

};

