#include "pch.h"
#include "EntityModel.h"


EntityModel::EntityModel(EEntityType EntityType, Transform TransformIn, Material* MaterialIn, std::string FileNameIn) : Entity(EntityType, TransformIn, MaterialIn, FileNameIn)
{
}

EntityModel::~EntityModel()
{
	delete Model;
}

void EntityModel::Initialise(GraphicsEngine * Graphics)
{
	Model = Graphics->CreateModel(FileName, EntityTransform);
}
