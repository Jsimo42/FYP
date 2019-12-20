#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"

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

};

