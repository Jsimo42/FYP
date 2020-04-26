#pragma once

#include "Libs.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Shader.h"
#include "Vertex.h"

struct TextureInfo
{
	GLuint ID;
	std::string Type;
	aiString Path;
};

class Mesh
{
public:
	//Mesh Loading Constructor
	Mesh(Primitive* PrimitiveIn, glm::vec3 PositionIn = glm::vec3(0.f), glm::vec3 RotationIn = glm::vec3(0.f), glm::vec3 ScaleIn = glm::vec3(1.f)); //TODO Create Vector and Transform
	//Model Loading Constructor
	Mesh(std::vector<Vertex> VerticesIn, std::vector<GLuint> IndicesIn, std::vector<TextureInfo> TexturesIn);

	Mesh() {};
	~Mesh();

	void Render(Shader* ShaderIn);
	void RenderModel(Shader* ShaderIn);

	glm::vec3 GetPosition() { return WorldPosition; }
	glm::vec3 GetRotation() { return WorldRotation; }

	void SetPosition(glm::vec3 NewPosition) { WorldPosition = NewPosition; 	UpdateModelMatrix();};
	void SetRotation(glm::vec3 NewRotation);
	void SetScale(glm::vec3 NewScale) { WorldScale = NewScale; UpdateModelMatrix();};

	void Move(glm::vec3 MoveAmount) { WorldPosition += MoveAmount; UpdateModelMatrix();};
	void Rotate(glm::vec3 RotationAmount);
	void Scale(glm::vec3 ScaleAmount) { WorldScale += ScaleAmount; UpdateModelMatrix();};

	std::vector<TextureInfo> GetTextures() { return Textures; }
 
private:
	//Transforms
	glm::vec3 WorldPosition = glm::vec3(0.f);
	glm::vec3 WorldRotation = glm::vec3(0.f);
	glm::vec3 WorldScale = glm::vec3(1.f);

	unsigned NumVertices{ 0 };
	unsigned NumIndices{ 0 };	

	GLuint VAO ;
	GLuint VBO;
	GLuint EBO;

	GLuint ModelVAO;
	GLuint ModelVBO;
	GLuint ModelEBO;

	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;
	std::vector<TextureInfo> Textures;

	glm::mat4 ModelMatrix;

	void InitialiseMeshVAO(Primitive* PrimitiveIn);
	void InitialiseModelVAO();

	void UpdateUniforms(Shader* ShaderIn);
	void UpdateModelMatrix();


};

