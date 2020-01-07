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

Mesh::Mesh(std::vector<Vertex> VerticesIn, std::vector<GLuint> IndicesIn, std::vector<TextureInfo> TexturesIn)
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
	NumVertices = PrimitiveIn->GetNumVertices();
	NumIndices = PrimitiveIn->GetNumIndices();

	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, NumVertices * sizeof(Vertex), PrimitiveIn->GetVertices(), GL_STATIC_DRAW);

	if (NumIndices > 0)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumIndices * sizeof(GLuint), PrimitiveIn->GetIndices(), GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

}

void Mesh::InitialiseModelVAO()
{
	// Create buffers/arrays
	glCreateVertexArrays(1, &ModelVAO);
	glBindVertexArray(ModelVAO);

	glGenBuffers(1, &ModelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ModelVBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	if (Indices.size() > 0)
	{
		glGenBuffers(1, &ModelEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ModelEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TexCoord));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));

	glBindVertexArray(0);
}

void Mesh::UpdateUniforms(Shader * ShaderIn)
{
	ShaderIn->SetMat4fv(ModelMatrix, "VS_ModelMatrix");
}

void Mesh::UpdateModelMatrix()
{
	ModelMatrix = glm::mat4(1.f);

	ModelMatrix = glm::translate(ModelMatrix, WorldPosition);

	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(WorldRotation.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(WorldRotation.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(WorldRotation.z), glm::vec3(0.f, 0.f, 1.f));

	ModelMatrix = glm::scale(ModelMatrix, WorldScale);
}

