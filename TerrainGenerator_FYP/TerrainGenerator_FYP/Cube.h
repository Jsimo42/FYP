#pragma once

#include "Libs.h"
#include "Primitive.h"

class Cube : public Primitive
{
public:

	Cube() : Primitive()
	{
		Vertex Vertices[]
		{
			//Positions											//Normals						//TexCoords
			glm::vec3(-0.5f, 0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(0.f, 2.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(2.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, 0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(2.f, 2.f),	glm::vec3(0.f,0.f,0.f),

			glm::vec3(0.5f, 0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(0.f, 2.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(2.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(2.f, 2.f), 	glm::vec3(0.f,0.f,0.f)
		};

		unsigned NumVertices = sizeof(Vertices) / sizeof(Vertex);

		GLuint Indices[]
		{
			0,1,2,
			0,2,3,

			7,6,1,
			7,1,0,

			4,5,6,
			4,6,7,

			3,2,5,
			3,5,4
		};

		unsigned NumIndices = sizeof(Indices) / sizeof(GLuint);

		Set(Vertices, NumVertices, Indices, NumIndices);
	}
};