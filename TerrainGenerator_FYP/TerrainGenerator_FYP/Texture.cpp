#include "pch.h"
#include "Texture.h"


Texture::Texture(const cv::Mat Image, GLenum Type, GLuint TextureUnit) : TextureType(Type), ID(TextureUnit)
{
	LoadFromFile(Image);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::Bind(const int TextureUnit)
{
	glActiveTexture(GL_TEXTURE0 + TextureUnit);
	glBindTexture(TextureType, ID);
}

void Texture::UnBind()
{
	glActiveTexture(0);
	glBindTexture(TextureType, 0);
}

void Texture::LoadFromFile(const cv::Mat Image)
{	
	glGenTextures(1, &ID);
	glBindTexture(TextureType, ID);

	glTexParameteri(TextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(TextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (Image.data)
	{
		cv::flip(Image, Image, 0);
		
		glTexImage2D(TextureType, 0, GL_RGB, Image.cols, Image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, Image.ptr());
		glGenerateMipmap(TextureType);
	}
	else
	{
		std::cout << "Image Load Error" << std::endl;
	}

	glActiveTexture(0);
	glBindTexture(TextureType, 0);
}
