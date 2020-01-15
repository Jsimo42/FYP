#include "pch.h"
#include "Level.h"
#include "EntityMesh.h"
#include "EntityModel.h"


Level::Level()
{
}


Level::~Level()
{
	for (int i = 0; i < LayerVector.size(); i++)
	{
		delete LayerVector[i];
	}
}

void Level::CreateLevel(std::vector<std::string> FilePaths, GraphicsEngine* Graphics)
{
	for (int i = 0; i < FilePaths.size(); i++)
	{
		LayerVector.push_back(CreateLayer(FilePaths[i], Graphics, i));
		LayerCount++;
	}
}

void Level::Render(GraphicsEngine* Graphics)
{
	std::vector<Entity*> EntityVector;
	std::vector<Mesh*> MeshVector;

	for (int i = 0; i < LayerVector.size(); i++)
	{
		//TODO Combine Vectors
		EntityVector = LayerVector[i]->GetEntities();
		//std::move(LayerVector[i]->GetEntities().begin(), LayerVector[i]->GetEntities().end(), std::back_inserter(EntityVector));
	}

	for (int i = 0; i <  EntityVector.size(); i++)
	{
		MeshVector.push_back(EntityVector[i]->GetMesh());
	}

	Graphics->Render(MeshVector);
}

Layer* Level::CreateLayer(std::string FilePath, GraphicsEngine* Graphics, int LayerNum)
{
	Layer* NewLayer = new Layer();

	NewLayer->CreateLayer(FilePath, Graphics, LayerNum);

	return NewLayer;
}
