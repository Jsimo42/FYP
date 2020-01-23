#include "pch.h"
#include "Texture.h"


Texture::Texture(const char * FileName, GLenum Type, GLuint TextureUnit) : TextureType(Type), ID(TextureUnit)
{
	LoadFromFile(FileName);
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

void Texture::LoadFromFile(const char * FileName)
{
	if (ID)
	{
		glDeleteTextures(1, &ID);
	}

	unsigned char* Image = SOIL_load_image(FileName, &Width, &Height, NULL, SOIL_LOAD_RGBA);

	glGenTextures(1, &ID);
	glBindTexture(TextureType, ID);

	glTexParameteri(TextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(TextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (Image)
	{
		glTexImage2D(TextureType, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Image);
		glGenerateMipmap(TextureType);
	}
	else
	{
		std::cout << "Image Load Error: " << FileName << std::endl;
	}

	glActiveTexture(0);
	glBindTexture(TextureType, 0);
	SOIL_free_image_data(Image);
}
