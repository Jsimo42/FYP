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
	Agents.push_back(new Agent(EColour::EWhite, cv::Vec3b(255, 255, 255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EYellow, cv::Vec3b(0, 255, 255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EOrange, cv::Vec3b(6, 6, 6), true, EEntityType::ECube)); //TODO	
	Agents.push_back(new Agent(EColour::ERed, cv::Vec3b(0, 0, 255), false, EEntityType::EModel, "Models/nanosuit.obj"));
	Agents.push_back(new Agent(EColour::EPink, cv::Vec3b(255, 0, 255), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EPurple, cv::Vec3b(6, 6, 6), true, EEntityType::ECube)); //TODO
	Agents.push_back(new Agent(EColour::EDarkBlue, cv::Vec3b(6, 6, 6), true, EEntityType::ECube)); //TODO
	Agents.push_back(new Agent(EColour::EBlue, cv::Vec3b(255, 0, 0), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::ELightBlue, cv::Vec3b(255, 255, 0), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::ELightGreen, cv::Vec3b(6, 6, 6), true, EEntityType::ECube)); //TODO
	Agents.push_back(new Agent(EColour::EGreen, cv::Vec3b(0, 255, 0), true, EEntityType::ECube));
	Agents.push_back(new Agent(EColour::EBlack, cv::Vec3b(0, 0, 0), true, EEntityType::ECube));

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(MenuWindow, true);

	// Setup style
	ImGui::StyleColorsDark();

	bool Done = false;
	bool ShowAgentWindow = false;
	bool ShowModelWindow = false;
	int LayerCount = 1;

	char EmptyBuffer[64] = "";
	char LastBuffer[64] = "";
	std::string LayerInput = "";

	while (!Done)
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		{
			ImGui::Checkbox("Generate Ground", &bGenerateGround);

			ImGui::NewLine();

			char Buffer[64] = "";

			ImGui::Text("Layers/");

			ImGui::SameLine();

			ImGui::InputText("Input Layer", Buffer, IM_ARRAYSIZE(Buffer));
			
			ImGui::SameLine();

			ImGui::Button("Submit Layer");

			if (std::strcmp(Buffer, LastBuffer))
			{
				if (!std::strcmp(Buffer, EmptyBuffer))
				{
					LayerFilePaths.push_back("Layers/" + LayerInput);
				}

				LayerInput = Buffer;

				for (int i = 0; i < 64; i++)
				{
					LastBuffer[i] = Buffer[i];
				}
			}

			ImGui::Text("Submitted Layers");

			for (int i = 0; i < LayerFilePaths.size(); i++)
			{
				ImGui::Text(LayerFilePaths[i].c_str());

				ImGui::SameLine();

				ImGui::PushID(i);

				std::string ButtonLabel = "Delete##" + std::to_string(i + 1);

				if (ImGui::Button(ButtonLabel.data()))
				{
					LayerFilePaths.erase(LayerFilePaths.begin() + i);
				}

				ImGui::PopID();
			}

			if (ImGui::Button("Edit Agents"))
				ShowAgentWindow = true;

			if (ShowAgentWindow)
			{
				DrawAgentWindow(Agents, ShowAgentWindow);
			}

			if (ImGui::Button("Edit Models"))
				ShowModelWindow = true;

			if (ShowModelWindow)
			{
				DrawModelWindow(Agents, ShowModelWindow);
			}

			CheckEverythingComplete(LayerFilePaths, Agents);

			switch (FormComplete)
			{
			case EFormCompletion::ENeedsLayers:
				ImGui::Text("Please add at least 1 layer!");
				break;
			case EFormCompletion::ENeedsModels:
				ImGui::Text("Please make sure all Models have a file name provided!");
				break;
			default:
				break;
			}

			if (ImGui::Button("Submit"))
			{
				if (FormComplete == EFormCompletion::EDone)
				{
					Done = true;
				}
			}


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

void MainMenu::DrawAgentWindow(std::vector<Agent*> &Agents, bool &ShowWindow)
{
	ImGui::Begin("Agent Window", &ShowWindow);

	ImGui::NewLine();
	ImGui::Text("Agents");

	std::string MeshType = "";

	for (int i = 0; i < ColourNames.size(); i++)
	{
		ImGui::PushID(i);

		ImGui::Text(ColourNames[i].c_str());


		ImGui::Text("Mesh Type - ");

		ImGui::SameLine();

		switch (Agents[i]->MeshType)
		{
		case EEntityType::ECube:
			MeshType = "Cube";
			break;
		case EEntityType::EPyramid:
			MeshType = "Pyramid";
			break;
		case EEntityType::EModel:
			MeshType = "Model";
			break;
		default:
			break;
		}

		ImGui::Text(MeshType.c_str());

		ImGui::SameLine();

		std::string ButtonLabel = "ChangeMeshType##" + std::to_string(i + 1);

		if (ImGui::Button(ButtonLabel.data()))
		{
			switch (Agents[i]->MeshType)
			{
			case EEntityType::ECube:
				Agents[i]->MeshType = EEntityType::EPyramid;
				Agents[i]->bIsMesh = true;
				break;
			case EEntityType::EPyramid:
				Agents[i]->MeshType = EEntityType::EModel;
				Agents[i]->bIsMesh = false;
				break;
			case EEntityType::EModel:
				Agents[i]->MeshType = EEntityType::ECube;
				Agents[i]->bIsMesh = true;
				break;
			default:
				break;
			}
		}

		ImGui::PopID();

	}

	if (ImGui::Button("Submit"))
		ShowWindow = false;
	ImGui::End();
}

void MainMenu::DrawModelWindow(std::vector<Agent*> &Agents, bool &ShowWindow)
{
	ImGui::Begin("Model Window", &ShowWindow);

	for (int i = 0; i < Agents.size(); i++)
	{
		if (Agents[i]->MeshType == EEntityType::EModel)
		{
			ImGui::Text(ColourNames[Agents[i]->LayerColour].c_str());
			
			char Buffer[64] = "";

			ImGui::Text("Models/");

			ImGui::SameLine();

			ImGui::InputText("", Buffer, IM_ARRAYSIZE(Buffer));

			ImGui::SameLine();

			ImGui::Button("Submit File Name");

			if (std::strcmp(Buffer, LastBuffer))
			{
				if (!std::strcmp(Buffer, EmptyBuffer))
				{
					Agents[i]->FileName = "Models/" + ModelInput;
				}

			ModelInput = Buffer;

				for (int i = 0; i < 64; i++)
				{
					LastBuffer[i] = Buffer[i];
				}
			}

			ImGui::Text("Submitted File Name - ");

			ImGui::SameLine();

			ImGui::Text(Agents[i]->FileName.c_str());
		}
	}

	if (ImGui::Button("Submit"))
		ShowWindow = false;
	ImGui::End();

}

void MainMenu::CheckEverythingComplete(std::vector<std::string>& LayerFilePaths, std::vector<Agent*> &Agents)
{
	if (LayerFilePaths.size() == 0)
	{
		FormComplete = EFormCompletion::ENeedsLayers;
		return;
	}

	for (int i = 0; i < Agents.size(); i++)
	{
		if (Agents[i]->MeshType == EEntityType::EModel)
		{
			if (Agents[i]->FileName == "")
			{
				FormComplete =  EFormCompletion::ENeedsModels;
				return;
			}
		}
	}

	FormComplete = EFormCompletion::EDone;
}
