#pragma once

#include "Libs.h"

class Shader
{
public:
	Shader(const char* VertexFile, const char* FragmentFile, const char* GeometryFile = NULL);
	~Shader();

	//Usage
	void UseProgram();
	void UnuseProgram();

	//Uniform Setters
	void Set1f(GLfloat Value, const GLchar* UniformName);
	void Set1i(GLint Value, const GLchar* UniformName);

	void SetVec2f(glm::fvec2 Value, const GLchar* UniformName);
	void SetVec3f(glm::fvec3 Value, const GLchar* UniformName);
	void SetVec4f(glm::fvec4 Value, const GLchar* UniformName);

	void SetMat3fv(glm::mat3 Value, const GLchar* UniformName, GLboolean Transpose = GL_FALSE);
	void SetMat4fv(glm::mat4 Value, const GLchar* UniformName, GLboolean Transpose = GL_FALSE);
private:
	//Variables
	GLuint id;

	//Functions
	std::string LoadShaderSource(char* FileName);

	GLuint LoadShader(GLenum ShaderType, char* FileName);

	void LinkProgram(GLuint VertexShader, GLuint FragmentShader, GLuint GeometryShader);
};

