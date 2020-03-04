#pragma once
#include "Entity.h"

class EntityMesh : public Entity
{
public:
	EntityMesh(EEntityType EntityType, Transform TransformIn, Material* MaterialIn, std::string FileNameIn = "");

	void Initialise(GraphicsEngine* Graphics) override;

	Mesh* GetMesh() const { return Mesh; };

private:
	Mesh* Mesh{ nullptr };
};

