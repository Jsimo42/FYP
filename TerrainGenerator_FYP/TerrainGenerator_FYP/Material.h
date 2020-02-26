#pragma once

#include "Libs.h"
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, Texture* DiffuseTexture, Texture* NormalTexture, Texture* MetallicTexture, Texture* RoughnessTexture);
	Material() {}; //TODO Remove temp constructor

	void RenderMaterial(Shader& ShaderIn);
	void UnBindTextures();

private:
	glm::vec3 Ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::vec3 Diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 Specular = glm::vec3(0.5f, 0.5f, 0.5f);
	Texture* DiffuseTexture = new Texture("Textures/Test.jfif", GL_TEXTURE_2D, 0);
	Texture* NormalTexture = new Texture("Textures/NTest.png", GL_TEXTURE_2D, 1);
	Texture* MetallicTexture = new Texture("Textures/STest.png", GL_TEXTURE_2D, 2);
	Texture* RoughnessTexture = new Texture("Textures/RTest.png", GL_TEXTURE_2D, 3);

	void SendUniforms(Shader& ShaderIn);
};

