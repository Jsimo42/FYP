#include "pch.h"
#include "EntityModel.h"


EntityModel::EntityModel(EEntityType EntityType, Transform TransformIn, std::string FileNameIn) : Entity(EntityType, TransformIn, FileNameIn)
{
}

void EntityModel::Initialise(GraphicsEngine * Graphics)
{
	Model = Graphics->CreateModel(FileName, EntityTransform);
}
