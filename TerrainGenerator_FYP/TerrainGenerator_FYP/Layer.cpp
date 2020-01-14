#include "pch.h"
#include "Layer.h"


Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::CreateLayer(std::string FileName, GraphicsEngine* Graphics)
{
//TODO File Loading
	int XPos{ 0 };
	int YPos{ 0 };
	int ZPos{ 0 };

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Transform EntityTransform = Transform();
			EntityTransform.Position = glm::vec3(XPos, YPos, ZPos);
			EntityTransform.Rotation = glm::vec3(0, 0, 0);
			EntityTransform.Scale = glm::vec3(1, 1, 1);

			switch (TestLevel[i][j])
			{
			case 0:
				EntityVector.push_back(new Entity(EEntityType::ECube, EntityTransform));
				break;
			case 1:
				EntityVector.push_back(new Entity(EEntityType::EPyramid, EntityTransform));
			default:
				break;
			}

			XPos += 10;
		}
	}

	for (int i = 0; i < EntityVector.size(); i++)
	{
		EntityVector[i]->Initialise(Graphics);
	}
}

void Layer::Render(GraphicsEngine* Graphics)
{
	for (int i = 0; i < EntityVector.size(); i++)
	{
		EntityVector[i]->Render(Graphics);
	}
}
