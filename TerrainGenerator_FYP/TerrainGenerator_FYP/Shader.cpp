#include "pch.h"
#include "Shader.h"


Shader::Shader(const char* VertexFile, const char* FragmentFile, const char* GeometryFile)
{
	GLuint VertexShader = 0;
	GLuint FragmentShader = 0;
	GLuint GeometryShader = 0;

	VertexShader = LoadShader(GL_VERTEX_SHADER, (char*)VertexFile);
	FragmentShader = LoadShader(GL_FRAGMENT_SHADER, (char*)FragmentFile);

	if (GeometryFile != NULL)
	{
		FragmentShader = LoadShader(GL_GEOMETRY_SHADER, (char*)GeometryFile);
	}

	LinkProgram(VertexShader, FragmentShader, GeometryShader);


	//End
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	glDeleteShader(GeometryShader);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::UseProgram()
{
	glUseProgram(id);
}

void Shader::UnuseProgram()
{
	glUseProgram(0);
}

void Shader::Set1f(GLfloat Value, const GLchar * UniformName)
{
	UseProgram();

	glUniform1f(glGetUniformLocation(id, UniformName), Value);

	UnuseProgram();
}

void Shader::Set1i(GLint Value, const GLchar * UniformName)
{
	UseProgram();

	glUniform1i(glGetUniformLocation(id, UniformName), Value);

	UnuseProgram();
}

void Shader::SetVec2f(glm::fvec2 Value, const GLchar * UniformName)
{
	UseProgram();

	glUniform2fv(glGetUniformLocation(id, UniformName), 1, glm::value_ptr(Value));

	UnuseProgram();
}

void Shader::SetVec3f(glm::fvec3 Value, const GLchar * UniformName)
{
	UseProgram();

	glUniform3fv(glGetUniformLocation(id, UniformName), 1, glm::value_ptr(Value));

	UnuseProgram();
}

void Shader::SetVec4f(glm::fvec4 Value, const GLchar * UniformName)
{
	UseProgram();

	glUniform4fv(glGetUniformLocation(id, UniformName), 1, glm::value_ptr(Value));

	UnuseProgram();
}

void Shader::SetMat3fv(glm::mat3 Value, const GLchar * UniformName, GLboolean Transpose)
{
	UseProgram();

	glUniformMatrix3fv(glGetUniformLocation(id, UniformName), 1, Transpose, glm::value_ptr(Value));

	UnuseProgram();
}

void Shader::SetMat4fv(glm::mat4 Value, const GLchar * UniformName, GLboolean Transpose)
{
	UseProgram();

	glUniformMatrix4fv(glGetUniformLocation(id, UniformName), 1, Transpose, glm::value_ptr(Value));

	UnuseProgram();
}

std::string Shader::LoadShaderSource(char * FileName)
{
	std::string InSource = "";
	std::string Source = "";

	std::ifstream InFile;

	InFile.open(FileName);

	if (InFile.is_open())
	{
		while (std::getline(InFile, InSource))
		{
			Source += InSource + "\n";
		}
	}
	else
	{
		std::cout << "Error Load Shaders Could Not Open - " << FileName << std::endl;
	}

	InFile.close();

	return Source;
}

GLuint Shader::LoadShader(GLenum ShaderType, char * FileName)
{
	char InfoLog[512];
	GLint LoadSuccess;

	GLuint ShaderFile = glCreateShader(ShaderType);
	std::string ShaderSource = this->LoadShaderSource(FileName);
	const GLchar* Source = ShaderSource.c_str();
	glShaderSource(ShaderFile, 1, &Source, NULL);

	glCompileShader(ShaderFile);

	glGetShaderiv(ShaderFile, GL_COMPILE_STATUS, &LoadSuccess);

	if (!LoadSuccess)
	{
		glGetShaderInfoLog(ShaderFile, 512, NULL, InfoLog);
		std::cout << "Error : LoadShaders could not compile - " << FileName << std::endl;
		std::cout << InfoLog << std::endl;
	}

	return ShaderFile; return GLuint();
}

void Shader::LinkProgram(GLuint VertexShader, GLuint FragmentShader, GLuint GeometryShader)
{
	char InfoLog[512];
	GLint LoadSuccess;

	id = glCreateProgram();

	glAttachShader(id, VertexShader);

	glAttachShader(id, FragmentShader);

	if (GeometryShader)
	{
		glAttachShader(id, GeometryShader);
	}

	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &LoadSuccess);

	if (!LoadSuccess)
	{
		glGetProgramInfoLog(id, 512, NULL, InfoLog);
		std::cout << "Error : LoadShaders could not link" << std::endl;
		std::cout << InfoLog << std::endl;
	}

	UnuseProgram();
}
