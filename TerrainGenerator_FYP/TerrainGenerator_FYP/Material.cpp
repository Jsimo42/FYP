#include "pch.h"
#include "Material.h"


Material::Material(glm::vec3 AmbientIn, glm::vec3 DiffuseIn, glm::vec3 SpecularIn, GLint DiffuseTextureIn, GLint NormalTextureIn, GLint MetallicTextureIn, GLint RoughnessTextureIn)
{
	Ambient = AmbientIn;
	Diffuse = DiffuseIn;
	Specular = SpecularIn;
	DiffuseTexture = DiffuseTextureIn;
	NormalTexture = NormalTextureIn;
	MetallicTexture = MetallicTextureIn;
	RoughnessTexture = RoughnessTextureIn;
}

void Material::SendUniforms(Shader & ShaderIn)
{
	//TODO Set Names when created FS
	ShaderIn.SetVec3f(Ambient, "");
	ShaderIn.SetVec3f(Diffuse, "");
	ShaderIn.SetVec3f(Specular, "");
	ShaderIn.Set1i(DiffuseTexture, "");
	ShaderIn.Set1i(NormalTexture, "");
	ShaderIn.Set1i(MetallicTexture, "");
	ShaderIn.Set1i(RoughnessTexture, "");
}
