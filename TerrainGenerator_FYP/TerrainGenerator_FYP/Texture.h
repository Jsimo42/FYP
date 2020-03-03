#pragma once

#include "Libs.h"

class Texture
{
public:
	Texture(const cv::Mat Image, GLenum Type, GLuint TextureUnit);
	~Texture();

	GLuint GetID() const { return ID; };

	void Bind(const int TextureUnit);
	void UnBind();

private: 
	GLuint ID{99};
	GLenum TextureType;
	int Height;
	int Width;

	void LoadFromFile(const cv::Mat Image);
};

