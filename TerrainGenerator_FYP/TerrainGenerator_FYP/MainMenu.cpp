#include "pch.h"
#include "MainMenu.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"


MainMenu::~MainMenu()
{
}

bool MainMenu::Initialise(const int Width, const int Height, float GLMajorVer, float GLMinorVer)
{
	WindowWidth = Width;
	WindowHeight = Height;

	if (!InitialiseGLFW(GLMajorVer, GLMinorVer))
	{
		return false;
	}
	
	return true;
}

bool MainMenu::ShowMenu(bool & bGenerateGround, std::vector<std::string>& LayerFilePaths, std::vector<Agent*> &Agents)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(MenuWindow, true);

	// Setup style
	ImGui::StyleColorsDark();

	bool Done = false;
	int LayerCount = 1;

	while (!Done)
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		{
			ImGui::Checkbox("Generate Ground", &bGenerateGround);

			if (ImGui::Button("Add Layer"))
				LayerCount++;

			for (int i = 0; i < LayerCount; i++)
			{
				//Text Box to enter Layer Filepath
			}

			if (ImGui::Button("Submit"))
				Done = true;
		}


		
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(MenuWindow);
	}

	ImGui::DestroyContext(); 
	glfwTerminate();

	LayerFilePaths.push_back("Layers/Layer.png");
	LayerFilePaths.push_back("Layers/Layer2.png");
	LayerFilePaths.push_back("Layers/Layer3.png");
	//LayerFilePaths.push_back("Layers/Layer4.txt");

	Agents.push_back(new Agent(EColour::EWhite, cv::Vec3b(255,255,255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::ERed, cv::Vec3b(0, 0, 255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EBlue, cv::Vec3b(255, 0, 0), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EGreen, cv::Vec3b(0, 255, 0), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::ELightBlue, cv::Vec3b(255, 255, 0), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EYellow, cv::Vec3b(0, 255, 255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EPink, cv::Vec3b(255, 0, 255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EBlack, cv::Vec3b(0, 0, 0), true, EEntityType::ECube));

	//TODO Setup Model Loading
	//Agents.push_back(new Agent(EColour::ERed, cv::Vec3b(0, 0, 255), false, EEntityType::EModel, "Models/scene.fbx"));
	return true;
}

bool MainMenu::InitialiseGLFW(float GLMajorVer, float GLMinorVer)
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW Initialise Error" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLMajorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLMinorVer);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);

	MenuWindow = glfwCreateWindow(WindowWidth, WindowHeight, "Terrain Generator Menu", NULL, NULL);

	if (MenuWindow == nullptr)
	{
		std::cout << "Window Initialise Error" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwGetFramebufferSize(MenuWindow, (int*)&WindowWidth, (int*)&WindowHeight);
	//glfwSetFramebufferSizeCallback(Window, GraphicsEngine::WindowResize);

	glfwMakeContextCurrent(MenuWindow);

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
