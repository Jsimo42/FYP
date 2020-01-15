#pragma once

#include "Libs.h"

class Primitive
{
public:

	Primitive() {};
	virtual ~Primitive() {};

	void Set(const Vertex* VerticesIn, const unsigned NumVertices, const GLuint* IndicesIn, const unsigned NumIndices)
	{
		for (size_t i = 0; i < NumVertices; i++)
		{
			PrimVertices.push_back(VerticesIn[i]);
		}

		for (size_t i = 0; i < NumIndices; i++)
		{
			PrimIndices.push_back(IndicesIn[i]);
		}
	}

	Vertex* GetVertices()
	{
		return PrimVertices.data();
	}

	GLuint* GetIndices()
	{
		return PrimIndices.data();
	}

	const unsigned GetNumVertices()
	{
		return PrimVertices.size();
	}

	const unsigned GetNumIndices()
	{
		return PrimIndices.size();
	}

private:

	std::vector <Vertex> PrimVertices;
	std::vector <GLuint> PrimIndices;

};