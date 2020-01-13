#include "pch.h"
#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine(const char * WindowTitle, const int Width, const int Height, const int GLMajorVer, const int GLMinorVer) : WindowWidth(Width), WindowHeight(Height), GLMajorVersion(GLMajorVer), GLMinorVersion(GLMinorVer), MainCamera(glm::vec3(20.f, 5.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f))
{
	Window = nullptr;
	FrameBufferWidth = WindowWidth;
	FrameBufferHeight = WindowHeight;

	InitialiseGLFW();
	InitialiseWindow(WindowTitle);
	InitialiseGLEW();
	SetOpenGLOptions();
}

GraphicsEngine::~GraphicsEngine()
{
	glfwDestroyWindow(Window);
	glfwTerminate();

	//TODO Change to int
	for (int i = 0; i < ShaderVector.size(); i++)
	{
		delete ShaderVector[i];
	}

	for (int i = 0; i < MaterialVector.size(); i++)
	{
		delete MaterialVector[i];
	}

	for (int i = 0; i < TextureVector.size(); i++)
	{
		delete TextureVector[i];
	}

	for (int i = 0; i < ModelVector.size(); i++)
	{
		delete ModelVector[i];
	}

	for (int i = 0; i < MeshVector.size(); i++)
	{
		delete MeshVector[i];
	}

	for (int i = 0; i < LightVector.size(); i++)
	{
		delete LightVector[i];
	}
}

void GraphicsEngine::Initialise()
{
	InitialiseMatrices();
	InitialiseShaders();
	InitialiseTextures();
	InitialiseMaterials();
	InitialiseModels();
	InitialiseMeshes();
	InitialiseLights();
	InitialiseUniforms();
}

void GraphicsEngine::Update()
{
	glfwPollEvents();
	UpdateDeltaTime();
	UpdateInput();
}

void GraphicsEngine::UpdateDeltaTime()
{
	CurrentTime = (float)glfwGetTime();
	DeltaTime = CurrentTime - LastTime;
	LastTime = CurrentTime;
}

void GraphicsEngine::UpdateInput()
{
	glfwPollEvents();

	UpdateKeyboardInput();
	UpdateMouseInput();
	MainCamera.UpdateInput(DeltaTime, MouseOffsetX, MouseOffsetY);
}

void GraphicsEngine::UpdateKeyboardInput()
{
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, GLFW_TRUE);
	}

	if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		MainCamera.MoveCamera(DeltaTime, Forward);
	}

	if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		MainCamera.MoveCamera(DeltaTime, Back);
	}

	if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		MainCamera.MoveCamera(DeltaTime, Left);
	}

	if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		MainCamera.MoveCamera(DeltaTime, Right);
	}


	int ControllerAttatched = glfwJoystickPresent(GLFW_JOYSTICK_1);

	if (ControllerAttatched)
	{
		int Count;
		const float* Axis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &Count);

		if (Axis[0] < 0)
		{
			MainCamera.MoveCamera(DeltaTime, Left);
		}
		else if (Axis[0] > 0)
		{
			MainCamera.MoveCamera(DeltaTime, Right);
		}

		if (Axis[1] < 0)
		{
			MainCamera.MoveCamera(DeltaTime, Forward);
		}
		else if (Axis[1] > 0)
		{
			MainCamera.MoveCamera(DeltaTime, Back);
		}
	}
}

void GraphicsEngine::UpdateMouseInput()
{
	glfwGetCursorPos(Window, &CurrentMouseX, &CurrentMouseY);

	if (bFirstMouse)
	{
		LastMouseX = CurrentMouseX;
		LastMouseY = CurrentMouseY;
		bFirstMouse = false;
	}

	MouseOffsetX = CurrentMouseX - LastMouseX;
	MouseOffsetY = CurrentMouseY - LastMouseY;

	LastMouseX = CurrentMouseX;
	LastMouseY = CurrentMouseY;
}

int GraphicsEngine::GetWindowShouldClose()
{
	return glfwWindowShouldClose(Window);
}

void GraphicsEngine::SetWindowShouldClose()
{
	glfwSetWindowShouldClose(Window, GLFW_TRUE);
}

Primitive GraphicsEngine::CreatePrimitive(EPrimitive PrimitiveType, Transform MeshTransform)
{
	switch (PrimitiveType)
	{
	case EPrimitive::ECube:
		return MeshVector.push_back(new Mesh(&Cube()));
		break;
	case EPrimitive::EPyramid:
		return MeshVector.push_back(new Mesh(&Pyramid()));
		break;
	default:
		break;
	}

	MeshCount++;
}

bool GraphicsEngine::CreateModel(std::string FileName, Transform MeshTransform)
{
	ModelVector.push_back(new Model(FileName));
	ModelCount++;

	return true;
}

void GraphicsEngine::Render()
{
	ShaderVector[MainProgram]->UseProgram();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	UpdateUniforms();

	for
}

bool GraphicsEngine::InitialiseGLFW()
{
	return false;
}

bool GraphicsEngine::InitialiseWindow(const char * WindowTitle)
{
	return false;
}

bool GraphicsEngine::InitialiseGLEW()
{
	return false;
}

void GraphicsEngine::SetOpenGLOptions()
{
}

void GraphicsEngine::InitialiseMatrices()
{
}

void GraphicsEngine::InitialiseShaders()
{
}

void GraphicsEngine::InitialiseTextures()
{
}

void GraphicsEngine::InitialiseMaterials()
{
}

void GraphicsEngine::InitialiseModels()
{
}

void GraphicsEngine::InitialiseMeshes()
{
}

void GraphicsEngine::InitialiseLights()
{
}

void GraphicsEngine::InitialiseUniforms()
{
}

void GraphicsEngine::UpdateUniforms()
{
}
