#pragma once

#include "Libs.h"
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, Texture* DiffuseTexture, Texture* NormalTexture, Texture* MetallicTexture, Texture* RoughnessTexture);

	void RenderMaterial(Shader& ShaderIn);
	void UnBindTextures();

private:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	Texture* DiffuseTexture;
	Texture* NormalTexture;
	Texture* MetallicTexture;
	Texture* RoughnessTexture;

	void SendUniforms(Shader& ShaderIn);
};

