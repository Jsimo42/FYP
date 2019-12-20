#pragma once
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

