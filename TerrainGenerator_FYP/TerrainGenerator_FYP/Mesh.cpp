#include "pch.h"
#include "Mesh.h"


Mesh::Mesh(Primitive * PrimitiveIn, glm::vec3 PositionIn, glm::vec3 RotationIn, glm::vec3 ScaleIn)
{
	WorldPosition = PositionIn;
	WorldRotation = RotationIn;
	WorldScale = ScaleIn;

	InitialiseMeshVAO(PrimitiveIn);
	UpdateModelMatrix();
}

Mesh::Mesh(std::vector<Vertex> VerticesIn, std::vector<GLuint> IndicesIn, std::vector<Texture> TexturesIn)
{
	Vertices = VerticesIn;
	Indices = IndicesIn;
	Textures = TexturesIn;

	InitialiseModelVAO();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Render(Shader * ShaderIn)
{
	UpdateUniforms(ShaderIn);
	UpdateModelMatrix();

	ShaderIn->UseProgram();

	glBindVertexArray(VAO);

	if (NumIndices == 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

void Mesh::RenderModel(Shader * ShaderIn)
{
	ShaderIn->UseProgram();

	UpdateModelMatrix();
	UpdateUniforms(ShaderIn);

	unsigned int DiffuseNum = 1;
	unsigned int SpecularNum = 1;

	for (unsigned int i = 0; i < Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); //Activate Texture Unit

		//Retrieve texture number (the N in diffuse_textureN)
		std::string Number;
		std::string Name = Textures[i].Type;

		if (Name == "texture_diffuse")
		{
			Number = std::to_string(DiffuseNum++);	
			ShaderIn->Set1i(i, "myMat.diffuseTexture");
		}
		else if (Name == "texture_specular")
		{
			Number = std::to_string(SpecularNum++);
			ShaderIn->Set1i(i, "myMat.metallicTexture");
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Textures[i].ID);
	}

	//Draw mesh
	ShaderIn->UseProgram();
	glBindVertexArray(ModelVAO);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetRotation(glm::vec3 NewRotation)
{
	WorldRotation = NewRotation;

	if (WorldRotation.x > 360)
	{
		WorldRotation.x = WorldRotation.x - 360;
	}
	else if (WorldRotation.y > 360)
	{
		WorldRotation.y = WorldRotation.y - 360;
	}
	else if (WorldRotation.z > 360)
	{
		WorldRotation.z = WorldRotation.z - 360;
	}
}

void Mesh::Rotate(glm::vec3 RotationAmount)
{
	WorldRotation += RotationAmount;

	if (WorldRotation.x > 360)
	{
		WorldRotation.x = WorldRotation.x - 360;
	}
	else if (WorldRotation.y > 360)
	{
		WorldRotation.y = WorldRotation.y - 360;
	}
	else if (WorldRotation.z > 360)
	{
		WorldRotation.z = WorldRotation.z - 360;
	}
}

void Mesh::InitialiseMeshVAO(Primitive * PrimitiveIn)
{
}

void Mesh::InitialiseModelVAO()
{
}

void Mesh::UpdateUniforms(Shader * ShaderIn)
{
}

void Mesh::UpdateModelMatrix()
{
}

