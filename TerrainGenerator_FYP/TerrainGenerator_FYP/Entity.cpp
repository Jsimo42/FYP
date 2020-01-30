#include "pch.h"
#include "Entity.h"


Entity::Entity(EEntityType EntityType, Transform TransformIn, Material* MaterialIn, std::string FileNameIn) : Type (EntityType), EntityTransform(TransformIn), MeshMaterial(MaterialIn)
{
	EntityTransform = TransformIn;
}

Entity::~Entity()
{
	delete MeshMaterial;
}

