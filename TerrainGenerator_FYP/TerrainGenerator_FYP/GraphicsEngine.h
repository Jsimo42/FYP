#pragma once

#include "Libs.h"
#include "Camera.h"
#include "Shader.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	void Initialise();



	bool CreatePrimitive();
	bool CreateModel();

	void Render();

};

