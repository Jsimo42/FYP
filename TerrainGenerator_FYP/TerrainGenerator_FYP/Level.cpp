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

void Level::CreateLevel(bool bGenerateGround, std::vector<std::string> FilePaths, GraphicsEngine* Graphics, std::vector<Agent*> Agents)
{
	if (bGenerateGround)
	{
		LayerVector.push_back(CreateLayer("Layers/DefaultGround.png", Graphics, 1, Agents));
		LayerCount++;
	}

	for (int i = 0; i < FilePaths.size(); i++)
	{
		LayerVector.push_back(CreateLayer(FilePaths[i], Graphics, LayerCount, Agents));
		LayerCount++;
	}
}

void Level::Render(GraphicsEngine* Graphics)
{
	std::vector<Entity*> EntityVector;
	std::vector<Mesh*> MeshVector;
	std::vector<Model*> ModelVector;
	std::vector<Material*> MeshMaterialVector;
	std::vector<Material*> ModelMaterialVector;

	for (int i = 0; i < LayerVector.size(); i++)
	{
		std::vector<Entity*> NewEntityVector = LayerVector[i]->GetEntities();
		EntityVector.insert(EntityVector.end(), NewEntityVector.begin(), NewEntityVector.end());

		NewEntityVector.clear();
	}

	for (int i = 0; i <  EntityVector.size(); i++)
	{
		if (EntityVector[i]->GetEntityType() == EEntityType::EModel)
		{
			ModelVector.push_back(EntityVector[i]->GetModel());
			ModelMaterialVector.push_back(EntityVector[i]->GetMaterial());
		}
		else
		{
			MeshVector.push_back(EntityVector[i]->GetMesh());
			MeshMaterialVector.push_back(EntityVector[i]->GetMaterial());
		}

		
	}

	Graphics->Render(MeshVector, MeshMaterialVector);
	//TODO Put into 1 Function
	//Graphics->RenderModel(ModelVector, ModelMaterialVector);
}

Layer* Level::CreateLayer(std::string FilePath, GraphicsEngine* Graphics, int LayerNum, std::vector<Agent*> Agents)
{
	Layer* NewLayer = new Layer();

	NewLayer->CreateLayer(FilePath, Graphics, LayerNum, Agents);

	return NewLayer;
}
