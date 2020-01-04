#include "pch.h"
#include "GraphicsEngine.h"


GraphicsEngine::GraphicsEngine(const char * WindowTitle, const int Width, const int Height, const int GLMajorVer, const int GLMinorVer) : WindowWidth(Width), WindowHeight(Height), GLMajorVersion(GLMajorVer), GLMinorVersion(GLMinorVer), MainCamera(glm::vec3(20.f, 5.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f))
{
	Window = nullptr;
	FrameBufferWidth = WindowWidth;
	FrameBufferheight = WindowHeight;

	InitialiseGLFW();
	InitialiseWindow(WindowTitle);
	InitialiseGLEW();
	InitialiseOpenGLOptions();
}

GraphicsEngine::~GraphicsEngine()
{
	glfwDestroyWindow(Window);
	glfwTerminate();
	//TODO Change to int
	for (size_t i = 0; i < ShaderVector.size(); i++)
	{
		delete ShaderVector[i];
	}

	for (size_t i = 0; i < MaterialVector.size(); i++)
	{
		delete MaterialVector[i];
	}

	for (size_t i = 0; i < TextureVector.size(); i++)
	{
		delete TextureVector[i];
	}

	for (size_t i = 0; i < modelVector.size(); i++)
	{
		delete ModelVector[i];
	}

	for (size_t i = 0; i < MeshVector.size(); i++)
	{
		delete MeshVector[i];
	}

	for (size_t i = 0; i < LightVector.size(); i++)
	{
		delete LightVector[i];
	}
}

void GraphicsEngine::Initialise()
{
}

bool GraphicsEngine::CreatePrimitive()
{
	return false;
}

bool GraphicsEngine::CreateModel()
{
	return false;
}

void GraphicsEngine::Render()
{
}
