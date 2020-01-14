#include "pch.h"
#include "Entity.h"


Entity::Entity(EEntityType EntityType, Transform TransformIn, std::string FileNameIn) : Type (EntityType), EntityTransform(TransformIn)
{
	EntityTransform = TransformIn;
}

Entity::~Entity()
{
}

void Entity::Initialise(GraphicsEngine * Graphics)
{
	switch (Type)
	{
	case EEntityType::ECube:
		EntityMesh = Graphics->CreatePrimitive(EPrimitive::EPrimCube, EntityTransform);
		break;
	case EEntityType::EPyramid:
		EntityMesh = Graphics->CreatePrimitive(EPrimitive::EPrimPyramid, EntityTransform);
		break;
	case EEntityType::EModel:
		EntityModel = Graphics->CreateModel(FileName, EntityTransform);
		break;
	default:
		return;
		break;
	}
}

void Entity::Render(GraphicsEngine * Graphics)
{
	if (bMesh)
	{
		Graphics->RenderMesh(EntityMesh, EntityTransform, TextureVector);
	}
	else
	{
		Graphics->RenderModel(EntityModel, EntityTransform, TextureVector);
	}
}
