#include "pch.h"
#include "Layer.h"


Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::CreateLevel(std::string FileName)
{
	//Parse File
		//Create Entity at position
	int XPos{ 0 };
	int YPos{ 0 };
	int ZPos{ 0 };

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			switch (TestLevel[i][j])
			{
			case 0:
				EntityVector.push_back(new Entity(EEntityType::ECube, glm::vec3(XPos, YPos, ZPos), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
			}
			XPos++;
		}
		YPos++;
	}
}

void Layer::Render(GraphicsEngine * Graphics)
{
	for (int i = 0; i < EntityVector.size(); i++)
	{
		EntityVector[i]->Render(Graphics);
	}
}
