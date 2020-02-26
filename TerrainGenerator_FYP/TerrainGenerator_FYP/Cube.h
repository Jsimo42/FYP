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
			//Positions											//Normals						//TexCoords				//Tangents
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
			//Front
			0,1,2,
			2,3,0,
			//Bottom
			2,1,6,
			6,5,2,
			//Right
			3,2,5,
			5,4,3,
			//Top
			7,0,3,
			3,4,7,
			//Left
			7,6,1,
			1,0,7,
			//Back
			4,5,6,
			6,7,4
		};

		unsigned NumIndices = sizeof(Indices) / sizeof(GLuint);

		Set(Vertices, NumVertices, Indices, NumIndices);
	}
};