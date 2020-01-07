#pragma once

#include "Libs.h"

class Texture
{
public:
	Texture(const char* FileName, GLenum Type);
	~Texture();

	GLuint GetID() const { return ID; };

	void Bind(const int TextureUnit);
	void Unbind();

private: 
	GLuint ID;
	GLenum TextureType;
	int Height;
	int Width;

	void LoadFromFile(const char* FileName);
};

