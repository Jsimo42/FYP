#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"

class Entity
{
public:
	Entity(EEntityType EntityType, Transform TransformIn, std::string FileNameIn = "");
	~Entity();

	void Render(GraphicsEngine* Graphics);

private:
	EEntityType Type = EEntityType::ENone;
	Mesh* EntityMesh{ nullptr };
	Model* EntityModel{ nullptr };
	Transform EntityTransform;
	bool bMesh{ true };

	std::vector<Texture*> TextureVector;
	GraphicsEngine * Graphics;
};

