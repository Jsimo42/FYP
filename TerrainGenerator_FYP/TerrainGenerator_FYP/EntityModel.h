#pragma once
#include "Entity.h"

class EntityModel : public Entity
{
public:
	EntityModel(EEntityType EntityType, Transform TransformIn, Material* MaterialIn, std::string FileNameIn);

	void Initialise(GraphicsEngine* Graphics) override;

	Model* GetModel() const { return Model; };

private:

	Model* Model{ nullptr };
};

