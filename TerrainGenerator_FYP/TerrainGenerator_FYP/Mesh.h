#pragma once

#include "Libs.h"
#include "Primitive.h"
#include "Shader.h"
#include "Vertex.h"

struct Texture
{
	GLuint ID;
	std::string Type;
	aiString Path;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
};

