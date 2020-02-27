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
			//Front
			glm::vec3(-0.5f, 0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, 0.5f, 0.5f),						glm::vec3(0.f,0.f,1.f),			glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,0.f),

			//Back
			glm::vec3(0.5f, 0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),						glm::vec3(0.f,0.f,-1.f),		glm::vec2(1.f, 1.f), 	glm::vec3(0.f,0.f,0.f),

			//Top
			glm::vec3(-0.5f, 0.5f, 0.5f),						glm::vec3(0.f,1.f,0.f),			glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, 0.5f, 0.5f),						glm::vec3(0.f,1.f,0.f),			glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, 0.5f, -0.5f),						glm::vec3(0.f,1.f,0.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),						glm::vec3(0.f,1.f,0.f),			glm::vec2(1.f, 0.f), 	glm::vec3(0.f,0.f,0.f),

			//Bottom
			glm::vec3(-0.5f, -0.5f, 0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),

			//Left
			glm::vec3(-0.5f, 0.5f, 0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(0.f, 1.f), 	glm::vec3(0.f,0.f,0.f),

			//Right
			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, 0.5f, 0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, 0.5f, -0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
		};

		unsigned NumVertices = sizeof(Vertices) / sizeof(Vertex);

		GLuint Indices[]
		{
			//Front
			0,1,2,
			2,3,0,
			//Back
			4,5,6,
			6,7,4,
			//Top
			11,8,9,
			9,10,11,
			//Bottom
			13,12,15,
			15,14,13,
			//Left
			19,18,17,
			17,16,19,
			//Right
			21,20,23,
			23,22,21,
		};

		unsigned NumIndices = sizeof(Indices) / sizeof(GLuint);

		Set(Vertices, NumVertices, Indices, NumIndices);
	}
};