#include "pch.h"
#include "Layer.h"
#include "EntityMesh.h"


Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::CreateLayer(std::string FileName, GraphicsEngine* Graphics, int LayerNum)
{
	//TODO File Loading
	int Width{ 20 };
	int Depth{ 20 };

	int XPos{ -Width/2 };
	int YPos{ LayerNum - 1};
	int ZPos{ Depth/2 };

	char Line;

	std::fstream LayerFile(FileName);

	//TODO Image Loading
	cv::Mat Image;
	std::string ImageName = "Layers/Image.png";
	Image = cv::imread(ImageName, cv::IMREAD_COLOR);

	if (!Image.data)
	{
		std::cout << "Cant Load Image: " << ImageName << std::endl;
	}

	//cv::Vec3f Colour = Image.at<cv::Vec3f>(10, 10);

	//Colour[0];

	cv::Mat Image2;
	ImageName = "Textures/Test.jfif";
	Image2 = cv::imread(ImageName, cv::IMREAD_COLOR);

	Material* TestMat = new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image2, GL_TEXTURE_2D, 0), new Texture(Image2, GL_TEXTURE_2D, 1), new Texture(Image2, GL_TEXTURE_2D, 2), new Texture(Image2, GL_TEXTURE_2D, 3));

	if (LayerFile.is_open())
	{
		for (int i = 0; i < Depth; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				LayerFile >> std::skipws >> Line;

				Transform EntityTransform = Transform();
				EntityTransform.Position = glm::vec3(XPos, YPos, ZPos);
				EntityTransform.Rotation = glm::vec3(0, 0, 0);
				EntityTransform.Scale = glm::vec3(1, 1, 1);

				switch (Line)
				{
				case '1':
					EntityVector.push_back(new EntityMesh(EEntityType::ECube, EntityTransform, TestMat));
					break;
				case '2':
					EntityVector.push_back(new EntityMesh(EEntityType::EPyramid, EntityTransform, TestMat));
				default:
					break;
				}

				XPos += 1;
			}

			XPos = -Width/2;
			ZPos++;

			LayerFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		LayerFile.close();
	}

	for (int i = 0; i < EntityVector.size(); i++)
	{
		EntityVector[i]->Initialise(Graphics, TestMat);
	}
}

