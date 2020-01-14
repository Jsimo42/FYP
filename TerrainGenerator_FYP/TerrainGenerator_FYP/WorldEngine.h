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

	bool Initialise();

	void CreateMenu();

	bool CreateLevel(string FilePath, int Layer);

	void Run();

	void Update();
	void Render();

private:
	GraphicsEngine* Graphics{ nullptr };
	Level* MainLevel{ nullptr };

	std::vector<Model*> ModelVector;
	std::vector<Mesh*> MeshVector;

};

