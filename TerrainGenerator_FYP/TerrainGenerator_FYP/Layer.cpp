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
	int XPos{ 0 };
	int YPos{ LayerNum - 1 + LayerNum };
	int ZPos{ 0 };

	char Line;

	std::fstream LayerFile(FileName);

	int Width{ 20 };
	int Height{ 20 };


	if (LayerFile.is_open())
	{
		for (int i = 0; i < Height; i++)
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
				case '0':
					EntityVector.push_back(new EntityMesh(EEntityType::ECube, EntityTransform));
					break;
				case '1':
					EntityVector.push_back(new EntityMesh(EEntityType::EPyramid, EntityTransform));
				default:
					break;
				}

				XPos += 1;
			}

			XPos = 0;
			ZPos++;

			LayerFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		LayerFile.close();
	}

	for (int i = 0; i < EntityVector.size(); i++)
	{
		EntityVector[i]->Initialise(Graphics);
	}
}

