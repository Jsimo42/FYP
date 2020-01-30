#include "pch.h"
#include "Entity.h"


Entity::Entity(EEntityType EntityType, Transform TransformIn, std::string FileNameIn) : Type (EntityType), EntityTransform(TransformIn)
{
	EntityTransform = TransformIn;
}

Entity::~Entity()
{
	delete MeshMaterial;
}

