#include "pch.h"
#include "MainMenu.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"


MainMenu::~MainMenu()
{
}

void MainMenu::Initialise(GraphicsEngine* Graphics)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.WantCaptureMouse = true;
	ImGui_ImplGlfwGL3_Init(Graphics->GetWindow(), true);

	// Setup style
	ImGui::StyleColorsDark();
}

bool MainMenu::ShowMenu(bool & bGenerateGround, std::vector<std::string>& LayerFilePaths, std::vector<Agent*> &Agents, GraphicsEngine* Graphics)
{
	static float f = 0.0f;
	static int counter = 0;
	bool Done = false;

	if (ImGui::GetIO().WantCaptureMouse)
	{
		std::cout << "True" << std::endl;
	}

	while (!Done)
	{
		ImGui_ImplGlfwGL3_NewFrame();

		{
			static float f = 0.0f;
			static int counter = 0;
			ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    

			ImGui::Checkbox("Done", &Done);      // Edit bools storing our windows open/close state

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}


		
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(Graphics->GetWindow());
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();


	bGenerateGround = true;

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
