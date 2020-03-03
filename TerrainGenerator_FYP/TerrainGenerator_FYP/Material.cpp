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

	if (DiffuseTexture)
	{
		DiffuseTexture->Bind(DiffuseTexture->GetID());
	}

	if (NormalTexture)
	{
		NormalTexture->Bind(NormalTexture->GetID());
	}

	if (MetallicTexture)
	{
		MetallicTexture->Bind(MetallicTexture->GetID());
	}

	if (RoughnessTexture)
	{
		RoughnessTexture->Bind(RoughnessTexture->GetID());
	}
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
	ShaderIn.SetVec3f(Ambient, "MeshMaterial.Ambient");
	ShaderIn.SetVec3f(Diffuse, "MeshMaterial.Diffuse");
	ShaderIn.SetVec3f(Specular, "MeshMaterial.Specular");

	if (DiffuseTexture)
	{
		ShaderIn.Set1i(DiffuseTexture->GetID(), "MeshMaterial.DiffuseTexture");
	}

	if (NormalTexture)
	{
		ShaderIn.Set1i(NormalTexture->GetID(), "MeshMaterial.NormalTexture");
	}

	if (MetallicTexture)
	{
		ShaderIn.Set1i(MetallicTexture->GetID(), "MeshMaterial.MetallicTexture");
	}

	if (RoughnessTexture)
	{
		ShaderIn.Set1i(RoughnessTexture->GetID(), "MeshMaterial.RoughnessTexture");
	}
}
