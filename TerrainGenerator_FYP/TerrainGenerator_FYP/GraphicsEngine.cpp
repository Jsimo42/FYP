#include "pch.h"
#include "GraphicsEngine.h"
#include "Entity.h"
#include "EntityMesh.h"
#include "EntityModel.h"

GraphicsEngine::GraphicsEngine(const char * WindowTitle, const int Width, const int Height, const int GLMajorVer, const int GLMinorVer) : WindowName(WindowTitle), WindowWidth(Width), WindowHeight(Height), GLMajorVersion(GLMajorVer), GLMinorVersion(GLMinorVer), MainCamera(glm::vec3(0.f, 5.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f))
{
	Window = nullptr;
	FrameBufferWidth = WindowWidth;
	FrameBufferHeight = WindowHeight;
}

GraphicsEngine::~GraphicsEngine()
{
	glfwDestroyWindow(Window);
	glfwTerminate();

	for (unsigned int i = 0; i < ShaderVector.size(); i++)
	{
		delete ShaderVector[i];
	}

	for (unsigned int i = 0; i < TextureVector.size(); i++)
	{
		delete TextureVector[i];
	}

}

void GraphicsEngine::Initialise()
{
	InitialiseGLFW();
	InitialiseWindow(WindowName.c_str());
	InitialiseGLEW();
	SetOpenGLOptions();

	InitialiseMatrices();
	InitialiseShaders();
	InitialiseLights();
	InitialiseUniforms();
}

void GraphicsEngine::Update()
{
	ShaderVector[MainProgram]->UseProgram();
	glfwPollEvents();
	UpdateDeltaTime();
	UpdateInput();

	ShaderVector[MainProgram]->UnuseProgram();
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
	default:
		std::cout << "Create Primitive Error" << std::endl;
		return new Mesh();
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

void GraphicsEngine::Render(std::vector<Entity*> EntityVector)
{
	ShaderVector[MainProgram]->UseProgram();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	UpdateUniforms();

	ShaderVector[MainProgram]->SetVec3f(LightVector[0]->GetPosition(), "LightPosition");
	ShaderVector[MainProgram]->SetVec3f(LightVector[0]->GetRotation(), "LightRotation");

	for (unsigned int i = 0; i < LightVector.size(); i++)
	{
		ShaderVector[MainProgram]->Set1f(2.f, "MeshType");

		LightVector[i]->Render(ShaderVector[MainProgram]);
	}

	for (unsigned int i = 0; i < EntityVector.size(); i++)
	{
		if (EntityVector[i]->GetEntityType() == EEntityType::EModel)
		{
			ShaderVector[MainProgram]->Set1f(1.f, "MeshType");

			std::vector<Mesh*> MeshVector = EntityVector[i]->GetModel()->GetMesh();
			std::vector<Material*> MaterialVector = EntityVector[i]->GetModel()->GetMaterials();

			for (unsigned int j = 0; j < MeshVector.size(); j++)
			{
				MaterialVector[j]->RenderMaterial(ShaderVector[MainProgram]);
				MeshVector[j]->RenderModel(ShaderVector[MainProgram]);
				MaterialVector[j]->UnBindTextures();
			}
		}
		else
		{
			ShaderVector[MainProgram]->Set1f(0.f, "MeshType");
			
			EntityVector[i]->GetMaterial()->RenderMaterial(ShaderVector[MainProgram]);
			EntityVector[i]->GetMesh()->Render(ShaderVector[MainProgram]);
			EntityVector[i]->GetMaterial()->UnBindTextures();
		}
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
	LightVector.push_back(new Mesh(new Pyramid(), glm::vec3(0.f, 10.f, 0.f), glm::vec3(0.f, -1.f, 0.f), glm::vec3(1.f, 1.f, 1.f)));
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

	ShaderVector[MainProgram]->Set1i(ShaderSettings->LightingSetting, "LightingSetting");
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
	if (glfwGetCurrentContext() == Window)
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

		if (glfwGetKey(Window, GLFW_KEY_R) == GLFW_PRESS)
		{
			if (ShaderSettings->bChangeWireframe)
			{
				if (ShaderSettings->bWireframeEnabled)
				{
					ShaderSettings->bWireframeEnabled = false;
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
				else
				{
					ShaderSettings->bWireframeEnabled = true;
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
			}

			ShaderSettings->bChangeWireframe = false;
		}

		if (glfwGetKey(Window, GLFW_KEY_R) == GLFW_RELEASE)
		{
			ShaderSettings->bChangeWireframe = true;
		}

		if (glfwGetKey(Window, GLFW_KEY_1) == GLFW_PRESS)
		{
			ShaderSettings->LightingSetting = ShaderSettings->ENone;
		}

		if (glfwGetKey(Window, GLFW_KEY_2) == GLFW_PRESS)
		{
			ShaderSettings->LightingSetting = ShaderSettings->ESpotLight;
		}

		if (glfwGetKey(Window, GLFW_KEY_3) == GLFW_PRESS)
		{
			ShaderSettings->LightingSetting = ShaderSettings->EPointLight;
		}

		if (glfwGetKey(Window, GLFW_KEY_4) == GLFW_PRESS)
		{
			ShaderSettings->LightingSetting = ShaderSettings->EGlobalLighting;
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
