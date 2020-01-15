#pragma once

#include "Libs.h"
#include "Mesh.h"

class Model
{
public:
	Model() {};
	Model(std::string Path);

	void Render(Shader* ShaderIn);

	void SetPosition(glm::vec3 NewPosition);
	void SetRotation(glm::vec3 NewRotation);
	void SetScale(glm::vec3 NewScale);

	void Move(glm::vec3 MoveAmount);
	void Rotate(glm::vec3 RotationAmount);
	void Scale(glm::vec3 ScaleAmount);

private:
	std::vector<Mesh*> MeshVector;
	std::vector<TextureInfo> TextureVector;
	std::string Directory;

	void LoadModel(std::string Path);
	void ProcessNode(aiNode* Node, const aiScene* Scene);
	Mesh* ProcessMesh(aiMesh* MeshIn, const aiScene* Scene);
	std::vector<TextureInfo> LoadMaterialTextures(aiMaterial* Material, aiTextureType Type, std::string TypeName);
	GLint TextureFromFile(const char* Path, std::string Directory);
};

