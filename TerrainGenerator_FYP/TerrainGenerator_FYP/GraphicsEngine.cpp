#include "pch.h"
#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine(const char * WindowTitle, const int Width, const int Height, const int GLMajorVer, const int GLMinorVer) : WindowWidth(Width), WindowHeight(Height), GLMajorVersion(GLMajorVer), GLMinorVersion(GLMinorVer), MainCamera(glm::vec3(0.f, 5.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f))
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
}

void GraphicsEngine::Initialise()
{
	InitialiseMatrices();
	InitialiseShaders();
	InitialiseLights();
	InitialiseUniforms();
}

void GraphicsEngine::Update()
{
	glfwPollEvents();
	UpdateDeltaTime();
	UpdateInput();

	//LightVector[0] = MainCamera.GetCameraPosition();
}

int GraphicsEngine::GetWindowShouldClose()
{
	return glfwWindowShouldClose(Window);
}

void GraphicsEngine::SetWindowShouldClose()
{
	glfwSetWindowShouldClose(Window, GLFW_TRUE);
}

Mesh* GraphicsEngine::CreatePrimitive(EPrimitive PrimitiveType, Transform MeshTransform)
{
	Mesh* NewMesh{ nullptr };

	switch (PrimitiveType)
	{
	case EPrimitive::EPrimCube:
		NewMesh = new Mesh(&Cube());

		NewMesh->SetPosition(MeshTransform.Position);
		NewMesh->SetRotation(MeshTransform.Rotation);
		NewMesh->SetScale(MeshTransform.Scale);

		return NewMesh;
		break;
	case EPrimitive::EPrimPyramid:
		NewMesh = new Mesh(&Pyramid());
		
		NewMesh->SetPosition(MeshTransform.Position);
		NewMesh->SetRotation(MeshTransform.Rotation);
		NewMesh->SetScale(MeshTransform.Scale);

		return NewMesh;
		break;
	}
}

Model* GraphicsEngine::CreateModel(std::string FileName, Transform ModelTransform)
{
	Model* NewModel = new Model(FileName);

	NewModel->SetPosition(ModelTransform.Position);
	NewModel->SetRotation(ModelTransform.Rotation);
	NewModel->SetScale(ModelTransform.Scale);

	return NewModel;
}


void GraphicsEngine::Render(std::vector<Mesh*> MeshVectorIn, std::vector<Material*> MaterialVectorIn)
{
	ShaderVector[MainProgram]->UseProgram();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	UpdateUniforms();

	ShaderVector[MainProgram]->Set1f(0.f, "bIsModel");
	ShaderVector[MainProgram]->SetVec3f(LightVector[0], "LightPosition");

	for (int i = 0; i < MeshVectorIn.size(); i++)
	{
		MaterialVectorIn[i]->RenderMaterial(*ShaderVector[MainProgram]);
		MeshVectorIn[i]->Render(ShaderVector[MainProgram]);
		MaterialVectorIn[i]->UnBindTextures();
	}

	glfwSwapBuffers(Window);
	glFlush();

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	ShaderVector[MainProgram]->UnuseProgram();
}

void GraphicsEngine::RenderModel(std::vector<Model*> ModelVectorIn, std::vector<Material*> MaterialVectorIn)
{
	ShaderVector[MainProgram]->UseProgram();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	UpdateUniforms();

	ShaderVector[MainProgram]->Set1f(1.f, "bIsModel");
	ShaderVector[MainProgram]->SetVec3f(LightVector[0], "LightPosition");

	for (int i = 0; i < ModelVectorIn.size(); i++)
	{
		MaterialVectorIn[i]->RenderMaterial(*ShaderVector[MainProgram]);
		ModelVectorIn[i]->Render(ShaderVector[MainProgram]);
		MaterialVectorIn[i]->UnBindTextures();
	}

	glfwSwapBuffers(Window);
	glFlush();

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	ShaderVector[MainProgram]->UnuseProgram();
}

bool GraphicsEngine::InitialiseGLFW()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW Initialise Error" << std::endl;
		glfwTerminate();
		return false;
	}

	return true;
}

bool GraphicsEngine::InitialiseWindow(const char * WindowTitle)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLMinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);

	Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);

	if (Window == nullptr)
	{
		std::cout << "Window Initialise Error" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwGetFramebufferSize(Window, &FrameBufferWidth, &FrameBufferHeight);
	glfwSetFramebufferSizeCallback(Window, GraphicsEngine::WindowResize);

	glfwMakeContextCurrent(Window);

	return true;
}

bool GraphicsEngine::InitialiseGLEW()
{
	glewExperimental = GL_TRUE;

	//Error Check
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Initialise Error" << std::endl;
		glfwTerminate();
		
		return false;
	}
	return true;
}

void GraphicsEngine::SetOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_POLYGON_MODE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GraphicsEngine::InitialiseMatrices()
{
	ViewMatrix = glm::mat4(1.f);
	ViewMatrix = glm::lookAt(CameraPosition, CameraPosition + ForwardVector, WorldUp);

	ProjectionMatrix = glm::mat4(1.f);
	ProjectionMatrix = glm::perspective(glm::radians(FOV), (float)FrameBufferWidth / FrameBufferHeight, NearPlane, FarPlane);
}

void GraphicsEngine::InitialiseShaders()
{
	ShaderVector.push_back(new Shader("VertexShader.glsl", "FragmentShader.glsl"));
}

void GraphicsEngine::InitialiseLights()
{
	LightVector.push_back(glm::vec3(20.f, 5.f, 20.f));
}

void GraphicsEngine::InitialiseUniforms()
{
	ShaderVector[MainProgram]->SetMat4fv(ViewMatrix, "VS_ViewMatrix");
	ShaderVector[MainProgram]->SetMat4fv(ProjectionMatrix, "VS_ProjectionMatrix");
}

void GraphicsEngine::UpdateUniforms()
{
	ViewMatrix = MainCamera.GetViewMatrix();

	ShaderVector[MainProgram]->SetMat4fv(ViewMatrix, "VS_ViewMatrix");
	ShaderVector[MainProgram]->SetVec3f(MainCamera.GetCameraPosition(), "CameraPosition");

	//Recalculate Projection Matrix
	glfwGetFramebufferSize(Window, &FrameBufferWidth, &FrameBufferHeight);

	ProjectionMatrix = glm::mat4(1.f);
	ProjectionMatrix = glm::perspective(glm::radians(FOV), (float)FrameBufferWidth / FrameBufferHeight, NearPlane, FarPlane);

	ShaderVector[MainProgram]->SetMat4fv(ProjectionMatrix, "VS_ProjectionMatrix");
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
		MainCamera.MoveCamera(DeltaTime, EForward);
	}

	if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		MainCamera.MoveCamera(DeltaTime, EBack);
	}

	if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		MainCamera.MoveCamera(DeltaTime, ELeft);
	}

	if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		MainCamera.MoveCamera(DeltaTime, ERight);
	}

	if (glfwGetKey(Window, GLFW_KEY_E) == GLFW_PRESS)
	{
		MainCamera.MoveCamera(DeltaTime, EUp);
	}

	if (glfwGetKey(Window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		MainCamera.MoveCamera(DeltaTime, EDown);
	}

	int ControllerAttatched = glfwJoystickPresent(GLFW_JOYSTICK_1);

	if (ControllerAttatched)
	{
		int Count;
		const float* Axis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &Count);

		if (Axis[0] < 0)
		{
			MainCamera.MoveCamera(DeltaTime, ELeft);
		}
		else if (Axis[0] > 0)
		{
			MainCamera.MoveCamera(DeltaTime, ERight);
		}

		if (Axis[1] < 0)
		{
			MainCamera.MoveCamera(DeltaTime, EForward);
		}
		else if (Axis[1] > 0)
		{
			MainCamera.MoveCamera(DeltaTime, EBack);
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

void GraphicsEngine::WindowResize(GLFWwindow * WindowIn, int Width, int Height)
{
	glViewport(0, 0, Width, Height);
}