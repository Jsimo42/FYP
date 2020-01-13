#pragma once

#include "Libs.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"


enum EShader { MainProgram = 0 };

enum EPrimitive 
{
	EPrimCube = 0,
	EPrimPyramid
};

class GraphicsEngine
{
public:
	GraphicsEngine(const char* WindowTitle, const int Width, const int Height, const int GLMajorVer, const int GLMinorVer);
	~GraphicsEngine();

	void Initialise();

	void Update();

	int GetWindowShouldClose();
	void SetWindowShouldClose();

	Mesh* CreatePrimitive(EPrimitive PrimitiveType, Transform MeshTransform);
	Model* CreateModel(std::string FileName, Transform MeshTransform);

	void RenderMesh(Mesh* RenderMesh, Transform MeshTransform, std::vector<Texture*> TextureVectorIn);
	void RenderModel(Model* RenderModel, Transform ModelTransform, std::vector<Texture*> TextureVectorIn);

private:

	//Window
	GLFWwindow* Window{ nullptr };
	int WindowWidth{ 0 };
	int WindowHeight{ 0 };
	int FrameBufferWidth{ 0 };
	int FrameBufferHeight{ 0 };
	const int GLMajorVersion = 4;
	const int GLMinorVersion = 6;

	//Mouse Input
	bool bFirstMouse{ true };
	double LastMouseX{ 0.f };
	double LastMouseY{ 0.f };
	double CurrentMouseX{ 0.f };
	double CurrentMouseY{ 0.f };
	double MouseOffsetX{ 0.f };
	double MouseOffsetY{ 0.f };

	//Delta time
	float DeltaTime{ 0.f };
	float CurrentTime{ 0.f };
	float LastTime{ 0.f };

	//Vectors
	std::vector <Shader*> ShaderVector;
	std::vector <TextureInfo*> TextureVector;
	std::vector <glm::vec3*> LightVector;

	//MVP Matrices
	glm::mat4 ViewMatrix = glm::mat4(0.f);
	glm::vec3 CameraPosition = glm::vec3{ 0.f, 0.f, 1.f };
	glm::vec3 WorldUp{ 0.f,1.f,0.f };
	glm::vec3 ForwardVector{ 0.f,0.f,-1.f };
	float FOV{ 90.f };
	float NearPlane{ 0.1f };
	float FarPlane{ 100.f };
	glm::mat4 ProjectionMatrix = glm::mat4(0.f);

	//Other
	Camera MainCamera;

	bool InitialiseGLEW();
	bool InitialiseGLFW();
	bool InitialiseWindow(const char* WindowTitle);
	void SetOpenGLOptions();

	void InitialiseMatrices();
	void InitialiseShaders();
	void InitialiseLights();
	void InitialiseUniforms();

	void UpdateUniforms();
	void UpdateDeltaTime();
	void UpdateInput();
	void UpdateKeyboardInput();
	void UpdateMouseInput();

	static void FrameBufferResizeCallback(GLFWwindow* WindowIn, int Width, int Height);
};

