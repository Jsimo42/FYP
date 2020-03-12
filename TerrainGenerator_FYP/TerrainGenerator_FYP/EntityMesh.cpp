#include "pch.h"
#include "EntityMesh.h"


EntityMesh::EntityMesh(EEntityType EntityType, Transform TransformIn, Material* MaterialIn, std::string FileNameIn) : Entity(EntityType, TransformIn, MaterialIn, FileNameIn)
{
}

EntityMesh::~EntityMesh()
{
	delete Mesh;
}

void EntityMesh::Initialise(GraphicsEngine * Graphics)
{
	switch (Type)
	{
	case EEntityType::ECube:
		Mesh = Graphics->CreatePrimitive(EPrimitive::EPrimCube, EntityTransform);
		break;
	case EEntityType::EPyramid:
		Mesh = Graphics->CreatePrimitive(EPrimitive::EPrimPyramid, EntityTransform);
		break;
	default:
		return;
		break;
	}
}
