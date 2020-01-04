#pragma once

#include "Libs.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
#include "Material.h"

enum EShader { MainProgram = 0 };

enum EPrimitive 
{
	Cube = 0,
	Pyramid
};

class GraphicsEngine
{
public:
	GraphicsEngine(const char* WindowTitle, const int Width, const int Height, const int GLMajorVer, const int GLMinorVer);
	~GraphicsEngine();

	void Initialise();

	bool CreatePrimitive();
	bool CreateModel();

	void Render();

private:
	std::vector <Shader*> ShaderVector;
	std::vector <Texture*> TextureVector;
	std::vector <Material*> MaterialVector;
	std::vector <Model*> odelVector;
	std::vector <Mesh*> MeshVector;
	std::vector <glm::vec3*> LightVector;
};

