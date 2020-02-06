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
		LayerVector.push_back(CreateLayer(FilePaths[i], Graphics, LayerCount));
		LayerCount++;
	}
}

void Level::Render(GraphicsEngine* Graphics)
{
	std::vector<Entity*> EntityVector;
	std::vector<Mesh*> MeshVector;
	std::vector<Material*> MaterialVector;

	for (int i = 0; i < LayerVector.size(); i++)
	{
		std::vector<Entity*> NewEntityVector = LayerVector[i]->GetEntities();
		EntityVector.insert(EntityVector.end(), NewEntityVector.begin(), NewEntityVector.end());

		NewEntityVector.clear();
	}

	for (int i = 0; i <  EntityVector.size(); i++)
	{
		MeshVector.push_back(EntityVector[i]->GetMesh());
		MaterialVector.push_back(EntityVector[i]->GetMaterial());
	}

	Graphics->Render(MeshVector, MaterialVector);
}

Layer* Level::CreateLayer(std::string FilePath, GraphicsEngine* Graphics, int LayerNum)
{
	Layer* NewLayer = new Layer();

	NewLayer->CreateLayer(FilePath, Graphics, LayerNum);

	return NewLayer;
}
