#include "pch.h"
#include "Entity.h"


Entity::Entity(EEntityType EntityType, Transform TransformIn, std::string FileNameIn)
{
	switch (EntityType)
	{
	case EEntityType::ECube:
		Graphics->CreatePrimitive(EPrimitive::EPrimCube, TransformIn);
		break;
	case EEntityType::EPyramid:
		Graphics->CreatePrimitive(EPrimitive::EPrimPyramid, TransformIn);
		break;
	case EEntityType::EModel:
		Graphics->CreateModel(FileNameIn, TransformIn);
		break;
	}
}

Entity::~Entity()
{
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
