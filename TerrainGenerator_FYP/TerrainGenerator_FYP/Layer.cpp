#include "pch.h"
#include "Layer.h"
#include "EntityMesh.h"
#include "EntityModel.h"


Layer::Layer()
{
}


Layer::~Layer()
{
	for (int i = 0; i < EntityVector.size(); i++)
	{
		delete EntityVector[i];
	}

	for (int i = 0; i < Materials.size(); i++)
	{
		//delete Materials[i];
	}
}

void Layer::CreateLayer(std::string FileName, GraphicsEngine* Graphics, int LayerNum, std::vector<Agent*> Agents)
{
	InitialiseMaterials();

	cv::Mat Layer;
	Layer = cv::imread(FileName, cv::IMREAD_COLOR);

	if (!Layer.data)
	{
		std::cout << "Cant Load Image: " << FileName << std::endl;
	}

	int Width = Layer.rows;
	int Depth = Layer.cols;

	int XPos{ -Width / 20 };
	int YPos{ LayerNum - 1 };
	int ZPos{ -Depth / 20 };

	cv::Vec3b Colour;
	EColour PreviousMeshColour = EColour::EWhite;
	int PreviousMeshID;

	for (int i = 1; i < Depth; i += 10)
	{
		for (int j = 1; j < Width; j += 10)
		{
			Colour = Layer.at<cv::Vec3b>(i, j);

			Transform EntityTransform = Transform();
			EntityTransform.Position = glm::vec3(XPos, YPos, ZPos);
			EntityTransform.Rotation = glm::vec3(0, 0, 0);
			EntityTransform.Scale = glm::vec3(1, 1, 1);

			if (GetNearestColour(Colour, Agents) == PreviousMeshColour && PreviousMeshColour != EColour::EWhite && EntityVector[PreviousMeshID - 1]->GetEntityType() == EEntityType::ECube)
			{
				float MovePositionX = (EntityVector[PreviousMeshID - 1]->GetScale().x / 2) - ((EntityVector[PreviousMeshID - 1]->GetScale().x - 1)/ 2);
				EntityVector[PreviousMeshID - 1]->Move(glm::vec3(MovePositionX, 0, 0));
				EntityVector[PreviousMeshID - 1]->Scale(glm::vec3(1, 0, 0));
				XPos++;
				continue;
			}
			
			switch (GetNearestColour(Colour, Agents))
			{
			case EWhite:
				//Leave Empty Space
				PreviousMeshColour = EColour::EWhite;
				break;
			case EYellow:
				if (Agents[1]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[1]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EYellow])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[1]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EYellow]), Agents[1]->FileName));
				}
				PreviousMeshColour = EColour::EYellow;
				break;
			case EOrange:
				if (Agents[2]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[2]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EOrange])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[2]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EOrange]), Agents[2]->FileName));
				}
				PreviousMeshColour = EColour::EOrange;
				break;
			case ERed:
				if (Agents[3]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[3]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::ERed])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[3]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::ERed]), Agents[3]->FileName));
				}
				PreviousMeshColour = EColour::ERed;
				break;
			case EPink:
				if (Agents[4]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[4]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EPink])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[4]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EPink]), Agents[4]->FileName));
				}
				PreviousMeshColour = EColour::EPink;
				break;
			case EPurple:
				if (Agents[5]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[5]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EPurple])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[5]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EPurple]), Agents[5]->FileName));
				}
				PreviousMeshColour = EColour::EPurple;
				break;
			case EDarkBlue:
				if (Agents[6]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[6]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EDarkBlue])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[6]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EDarkBlue]), Agents[6]->FileName));
				}
				PreviousMeshColour = EColour::EDarkBlue;
				break;
			case EBlue:
				if (Agents[7]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[7]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EBlue])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[7]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EBlue]), Agents[7]->FileName));
				}
				PreviousMeshColour = EColour::EBlue;
				break;
			case ELightBlue:
				if (Agents[8]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[8]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::ELightBlue])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[8]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::ELightBlue]), Agents[8]->FileName));
				}
				PreviousMeshColour = EColour::ELightBlue;
				break;
			case ELightGreen:
				if (Agents[9]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[9]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::ELightGreen])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[9]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::ELightGreen]), Agents[9]->FileName));
				}
				PreviousMeshColour = EColour::ELightGreen;
				break;
			case EGreen:
				if (Agents[10]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[10]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EGreen])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[10]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EGreen]), Agents[10]->FileName));
				}
				PreviousMeshColour = EColour::EGreen;
				break;
			case EBlack:
				if (Agents[11]->bIsMesh)
				{
					EntityVector.push_back(new EntityMesh(Agents[11]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EBlack])));
				}
				else
				{
					EntityVector.push_back(new EntityModel(Agents[11]->MeshType, EntityTransform, Materials.at(ColourNames[EColour::EBlack]), Agents[11]->FileName));
				}
				PreviousMeshColour = EColour::EBlack;
				break;
			default:
				break;
			}

			PreviousMeshID = EntityVector.size();
			XPos++;
		}

		PreviousMeshColour = EColour::EWhite;
		XPos = -Width/20;
		ZPos++;
	}

	for (int i = 0; i < EntityVector.size(); i++)
	{
		EntityVector[i]->Initialise(Graphics);
	}
}

void Layer::InitialiseMaterials()
{
	cv::Mat Image;
	Image = cv::imread("Textures/Red.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: Red" << std::endl;
	}
	else
	{
		Materials.insert({ "Red", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}
	
	Image = cv::imread("Textures/Blue.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: Blue" << std::endl;
	}
	else
	{
		Materials.insert({ "Blue", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}

	Image = cv::imread("Textures/Green.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: Green" << std::endl;
	}
	else
	{
		Materials.insert({ "Green", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}

	Image = cv::imread("Textures/Pink.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: Pink" << std::endl;
	}
	else
	{
		Materials.insert({ "Pink", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}

	Image = cv::imread("Textures/Yellow.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: Yellow" << std::endl;
	}
	else
	{
		Materials.insert({ "Yellow", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}

	Image = cv::imread("Textures/LightBlue.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: LightBlue" << std::endl;
	}
	else
	{
		Materials.insert({ "LightBlue", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}

	Image = cv::imread("Textures/White.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: White" << std::endl;
	}
	else
	{
		Materials.insert({ "Black", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}

	Image = cv::imread("Textures/Purple.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: Purple" << std::endl;
	}
	else
	{
		Materials.insert({ "Purple", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}

	Image = cv::imread("Textures/LightGreen.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: Light Green" << std::endl;
	}
	else
	{
		Materials.insert({ "LightGreen", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}

	Image = cv::imread("Textures/DarkBlue.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: Dark Blue" << std::endl;
	}
	else
	{
		Materials.insert({ "DarkBlue", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}

	Image = cv::imread("Textures/Orange.png", cv::IMREAD_COLOR);
	if (!Image.data)
	{
		std::cout << "Cant Load Image: Orange" << std::endl;
	}
	else
	{
		Materials.insert({ "Orange", new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), new Texture(Image, GL_TEXTURE_2D, 0), new Texture(Image, GL_TEXTURE_2D, 1), new Texture(Image, GL_TEXTURE_2D, 2), new Texture(Image, GL_TEXTURE_2D, 3)) });
	}
}

EColour Layer::GetNearestColour(cv::Vec3b ColourIn, std::vector<Agent*> Agents)
{
	float NearestR = 255 - ColourIn[2];
	float NearestG = 255 - ColourIn[1];
	float NearestB = 255 - ColourIn[0];
	
	if (NearestB < 63)
	{
		NearestB = 255;
	}
	else if (NearestB >= 63 && NearestB < 188)
	{
		NearestB = 125;
	}
	else if (NearestB >= 188)
	{
		NearestB = 0;
	}

	if (NearestG < 63)
	{
		NearestG = 255;
	}
	else if (NearestG >= 63 && NearestG < 188)
	{
		NearestG = 125;
	}
	else if (NearestG >= 188)
	{
		NearestG = 0;
	}

	if (NearestR < 63)
	{
		NearestR = 255;
	}
	else if (NearestR >= 63 && NearestR < 188)
	{
		NearestR = 125;
	}
	else if (NearestR >= 188)
	{
		NearestR = 0;
	}

	cv::Vec3b NewColour = cv::Vec3b(NearestB, NearestG, NearestR);

	for (int a = 0; a < Agents.size(); a++)
	{
		if (NewColour == Agents[a]->Colour)
		{
			return Agents[a]->LayerColour;
		}
	}
}
