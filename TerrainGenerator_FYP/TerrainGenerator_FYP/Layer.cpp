#include "pch.h"
#include "Layer.h"
#include "EntityMesh.h"
#include "EntityModel.h"


Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::CreateLayer(std::string FileName, GraphicsEngine* Graphics, int LayerNum, std::vector<Agent*> Agents)
{
	//TODO A4 Image size - 2480 x 3508
	int Width{ 320 };
	int Depth{ 320 };

	int XPos{ -Width / 20 };
	int YPos{ LayerNum - 1 };
	int ZPos{ -Depth / 20 };

	cv::Mat Image;
	Image = cv::imread("Textures/Red.png", cv::IMREAD_COLOR);
	std::unordered_map<std::string, Material*> Materials;
	Materials.insert({ "Red", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	
	Image = cv::imread("Textures/Blue.png", cv::IMREAD_COLOR);
	Materials.insert({ "Blue", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });

	Image = cv::imread("Textures/Green.png", cv::IMREAD_COLOR);
	Materials.insert({ "Green", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });

	Image = cv::imread("Textures/Pink.png", cv::IMREAD_COLOR);
	Materials.insert({ "Pink", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });

	Image = cv::imread("Textures/Yellow.png", cv::IMREAD_COLOR);
	Materials.insert({ "Yellow", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });

	Image = cv::imread("Textures/LightBlue.png", cv::IMREAD_COLOR);
	Materials.insert({ "LightBlue", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });

	Image = cv::imread("Textures/White.png", cv::IMREAD_COLOR);
	Materials.insert({ "White", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });

	cv::Mat Layer;
	Layer = cv::imread(FileName, cv::IMREAD_COLOR);

	if (!Layer.data)
	{
		std::cout << "Cant Load Image: " << FileName << std::endl;
	}

	cv::Vec3b Colour;

	for (int i = 1; i < Depth; i += 10)
	{
		for (int j = 1; j < Width; j += 10)
		{
			Colour = Layer.at<cv::Vec3b>(i, j);

			Transform EntityTransform = Transform();
			EntityTransform.Position = glm::vec3(XPos, YPos, ZPos);
			EntityTransform.Rotation = glm::vec3(0, 0, 0);
			EntityTransform.Scale = glm::vec3(1, 1, 1);

			//BGR
			for (int a = 0; a < Agents.size(); a++)
			{
				if (Colour == Agents[a]->Colour)
				{
					if (Agents[a]->bIsMesh)
					{
						EntityVector.push_back(new EntityMesh(Agents[a]->MeshType, EntityTransform, Materials.at(ColourNames[Agents[a]->LayerColour]))); //TODO  Materials.at(Agents[a]->LayerColour)
					}
					else
					{
						EntityVector.push_back(new EntityModel(Agents[a]->MeshType, EntityTransform, Materials.at("White"), Agents[a]->FileName));
					}
				}
			}

			XPos++;
		}

		XPos = -Width/20;
		ZPos++;
	}

	for (int i = 0; i < EntityVector.size(); i++)
	{
		EntityVector[i]->Initialise(Graphics);
	}
}

