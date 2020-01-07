#pragma once

#include "Libs.h"
#include "Shader.h"

class Material
{
public:
	Material(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, GLint DiffuseTexture, GLint NormalTexture, GLint MetallicTexture, GLint RoughnessTexture);

	void SendUniforms(Shader& ShaderIn);

private:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	GLint DiffuseTexture;
	GLint NormalTexture;
	GLint MetallicTexture;
	GLint RoughnessTexture;
};

