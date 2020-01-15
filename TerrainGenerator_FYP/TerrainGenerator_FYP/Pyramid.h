#pragma once

#include "Libs.h"
#include "Primitive.h"

class Pyramid : public Primitive
{
public:

	Pyramid() : Primitive()
	{
		Vertex Vertices[]
		{
			//Positions											//Normals						//TexCoords
			glm::vec3(0.f, 0.5f, 0.f),							glm::vec3(0.f,0.f,1.f),			glm::vec2(0.5f,1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),

			glm::vec3(0.f, 0.5f, 0.f),							glm::vec3(-1.f,0.f,0.f),		glm::vec2(0.5f,1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),

			glm::vec3(0.f, 0.5f, 0.f),							glm::vec3(0.f,0.f,-1.f),		glm::vec2(0.5f,1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),

			glm::vec3(0.f, 0.5f, 0.f),							glm::vec3(1.f,0.f,0.f),			glm::vec2(0.5f,1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),

			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(0.f,-1.f,0.f),			glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),						glm::vec3(0.f,-1.f,0.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),

			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(0.f,-1.f,0.f),			glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f)
		};

		unsigned NumVertices = sizeof(Vertices) / sizeof(Vertex);

		Set(Vertices, NumVertices, nullptr, 0);
	}
};