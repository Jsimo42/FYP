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
			//Front - Facing Left
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
			glm::vec3(0.5f, 0.5f, 0.5f),						glm::vec3(0.f,1.f,0.f),			glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, 0.5f, -0.5f),						glm::vec3(0.f,1.f,0.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),						glm::vec3(0.f,1.f,0.f),			glm::vec2(1.f, 0.f), 	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, 0.5f, 0.5f),						glm::vec3(0.f,1.f,0.f),			glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,0.f),

			//Bottom
			glm::vec3(-0.5f, -0.5f, 0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(0.f,-1.f,0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,0.f),

			//Left
			glm::vec3(-0.5f, 0.5f, -0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(0.f, 1.f), 	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(-0.5f, 0.5f, 0.5f),						glm::vec3(-1.f,0.f,0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			
			//Right
			glm::vec3(0.5f, 0.5f, 0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.5f, 0.5f, -0.5f),						glm::vec3(1.f,0.f,0.f),			glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,0.f),
			
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
			8,9,10,
			10,11,8,
			//Bottom
			12,13,14,
			14,15,12,
			//Left
			16,17,18,
			18,19,16,
			//Right
			20,21,22,
			22,23,20,
		};

		unsigned NumIndices = sizeof(Indices) / sizeof(GLuint);

		Set(Vertices, NumVertices, Indices, NumIndices);
	}
};