#include "pch.h"
#include "Model.h"


Model::Model(GLchar * Path)
{
	LoadModel(Path);
}

void Model::Render(Shader * ShaderIn)
{
	for (int i = 0; i < MeshVector.size(); i++)
	{
		MeshVector[i]->RenderModel(ShaderIn);
	}
}

void Model::SetPosition(glm::vec3 NewPosition)
{
	for (int i = 0; i < MeshVector.size(); i++)
	{
		MeshVector[i]->SetPosition(NewPosition);
	}
}

void Model::SetRotation(glm::vec3 NewRotation)
{
	for (int i = 0; i < MeshVector.size(); i++)
	{
		MeshVector[i]->SetRotation(NewRotation);
	}
}

void Model::SetScale(glm::vec3 NewScale)
{
	for (int i = 0; i < MeshVector.size(); i++)
	{
		MeshVector[i]->SetScale(NewScale);
	}
}

void Model::Move(glm::vec3 MoveAmount)
{
	for (int i = 0; i < MeshVector.size(); i++)
	{
		MeshVector[i]->Move(MoveAmount);
	}
}

void Model::Rotate(glm::vec3 RotationAmount)
{
	for (int i = 0; i < MeshVector.size(); i++)
	{
		MeshVector[i]->Rotate(RotationAmount);
	}
}

void Model::Scale(glm::vec3 ScaleAmount)
{
	for (int i = 0; i < MeshVector.size(); i++)
	{
		MeshVector[i]->Scale(ScaleAmount);
	}
}

void Model::LoadModel(std::string Path)
{
	Assimp::Importer Importer;
	const aiScene* Scene = Importer.ReadFile(Path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

	if (!Scene || Scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
	{
		std::cout << "Assimp Error: " << Importer.GetErrorString() << std::endl;
		return;
	}

	Directory = Path.substr(0, Path.find_last_of('/'));
	ProcessNode(Scene->mRootNode, Scene);
}

void Model::ProcessNode(aiNode* Node, const aiScene* Scene)
{
	for (int i = 0; i < Node->mNumMeshes; i++)
	{
		aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
		MeshVector.push_back(ProcessMesh(Mesh, Scene));
	}

	for (int i = 0; i < Node->mNumChildren; i++)
	{
		ProcessNode(Node->mChildren[i], Scene);
	}
}

Mesh* Model::ProcessMesh(aiMesh* MeshIn, const aiScene* Scene)
{
	std::vector<Vertex> VertexVector;
	std::vector<GLuint> IndexVector;
	std::vector<Texture> TextureVector;

	//Process Vertices
	for (int i = 0; i < MeshIn->mNumVertices; i++)
	{
		Vertex Vertex;
		glm::vec3 Vector;

		Vector.x = MeshIn->mVertices[i].x;
		Vector.y = MeshIn->mVertices[i].y;
		Vector.z = MeshIn->mVertices[i].z;
		Vertex.Position = Vector;

		Vector.x = MeshIn->mNormals[i].x;
		Vector.y = MeshIn->mNormals[i].y;
		Vector.z = MeshIn->mNormals[i].z;
		Vertex.Normal = Vector;

		if (MeshIn->mTextureCoords[0])
		{
			glm::vec2 Vec;
			Vec.x = MeshIn->mTextureCoords[0][i].x;
			Vec.y = MeshIn->mTextureCoords[0][i].y;
			Vertex.TexCoord = Vec;
		}
		else
		{
			Vertex.TexCoord = glm::vec2(0.0f, 0.0f);
		}

		Vector.x = MeshIn->mTangents[i].x;
		Vector.y = MeshIn->mTangents[i].y;
		Vector.z = MeshIn->mTangents[i].z;
		Vertex.Tangent = Vector;

		VertexVector.push_back(Vertex);
	}

	//Process Indices
	for (int i = 0; i < MeshIn->mNumFaces; i++)
	{
		aiFace Face = MeshIn->mFaces[i];

		for (int j = 0; j < Face.mNumIndices; j++)
		{
			IndexVector.push_back(Face.mIndices[j]);
		}
	}

	// Process materials
	if (MeshIn->mMaterialIndex >= 0)
	{
		aiMaterial* material = Scene->mMaterials[MeshIn->mMaterialIndex];

		std::vector<Texture> DiffuseMaps = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		TextureVector.insert(TextureVector.end(), DiffuseMaps.begin(), DiffuseMaps.end());

		std::vector<Texture> SpecularMaps = this->LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		TextureVector.insert(TextureVector.end(), SpecularMaps.begin(), SpecularMaps.end());
	}

	Mesh* ProcessedMesh = new Mesh(VertexVector, IndexVector, TextureVector);
	return ProcessedMesh;
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* Material, aiTextureType Type, std::string TypeName)
{
	std::vector<Texture> TexVector;

	for (int i = 0; i < Material->GetTextureCount(Type); i++)
	{
		aiString String;
		Material->GetTexture(Type, i, &String);
		GLboolean skip = false;

		for (int j = 0; j < TextureVector.size(); j++)
		{
			if (TextureVector[j].Path == String)
			{
				TexVector.push_back(TextureVector[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			Texture Texture;
			Texture.ID = TextureFromFile(String.C_Str(), Directory);
			Texture.Type = TypeName;
			Texture.Path = String;
			TexVector.push_back(Texture);

			TextureVector.push_back(Texture);
		}
	}

	return TexVector;
}

GLint Model::TextureFromFile(const char* Path, std::string Directory)
{
	//Generate texture ID and load texture data
	std::string FilePath = std::string(Path);
	FilePath = Directory + '/' + FilePath;
	GLuint TextureID;
	glGenTextures(1, &TextureID);

	int Width{ 0 };
	int Height{ 0 };

	unsigned char* Image = SOIL_load_image(FilePath.c_str(), &Width, &Height, 0, SOIL_LOAD_RGB);

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(Image);

	return TextureID;
}
