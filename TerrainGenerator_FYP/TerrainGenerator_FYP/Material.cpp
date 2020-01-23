#include "pch.h"
#include "Material.h"


Material::Material(glm::vec3 AmbientIn, glm::vec3 DiffuseIn, glm::vec3 SpecularIn, Texture* DiffuseTextureIn, Texture* NormalTextureIn, Texture* MetallicTextureIn, Texture* RoughnessTextureIn)
{
	Ambient = AmbientIn;
	Diffuse = DiffuseIn;
	Specular = SpecularIn;
	DiffuseTexture = DiffuseTextureIn;
	NormalTexture = NormalTextureIn;
	MetallicTexture = MetallicTextureIn;
	RoughnessTexture = RoughnessTextureIn;
}

void Material::RenderMaterial(Shader & ShaderIn)
{
	SendUniforms(ShaderIn);

	DiffuseTexture->Bind(0);
	NormalTexture->Bind(1);
	MetallicTexture->Bind(2);
	RoughnessTexture->Bind(3);
}

void Material::UnBindTextures()
{
	DiffuseTexture->UnBind();
	NormalTexture->UnBind();
	MetallicTexture->UnBind();
	RoughnessTexture->UnBind();
}

void Material::SendUniforms(Shader & ShaderIn)
{
	//TODO Set Names when created FS
	ShaderIn.SetVec3f(Ambient, "MeshMaterial.Ambient");
	ShaderIn.SetVec3f(Diffuse, "MeshMaterial.Diffuse");
	ShaderIn.SetVec3f(Specular, "MeshMaterial.Specular");
	ShaderIn.Set1i(DiffuseTexture->GetID(), "MeshMaterial.DiffuseTexture");
	ShaderIn.Set1i(NormalTexture->GetID(), "MeshMaterial.NormalTexture");
	ShaderIn.Set1i(MetallicTexture->GetID(), "MeshMaterial.MetallicTexture");
	ShaderIn.Set1i(RoughnessTexture->GetID(), "MeshMaterial.RoughnessTexture");
}
