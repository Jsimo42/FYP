#pragma once
#include "Entity.h"

class EntityModel : public Entity
{
public:
	EntityModel(EEntityType EntityType, Transform TransformIn, std::string FileNameIn);

	void Initialise(GraphicsEngine* Graphics, Material* MeshMaterialIn) override;

	Model* GetModel() const { return Model; };

private:

	std::string FileName{ "" };
	Model* Model{ nullptr };
};

