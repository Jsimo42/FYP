#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"

class Entity
{
public:
	Entity(EEntityType EntityType, Transform TransformIn, std::string FileNameIn = "");
	~Entity();

	void Initialise(GraphicsEngine* Graphics);

	Mesh* GetMesh() const { return EntityMesh; };
	Model* GetModel() const{ return EntityModel; };

private:
	EEntityType Type = EEntityType::ENone;
	
	Mesh* EntityMesh{ nullptr };

	std::string FileName{ "" };
	Model* EntityModel{ nullptr };

	Transform EntityTransform = Transform();
	bool bMesh{ true };

	std::vector<Texture*> TextureVector;
	GraphicsEngine * Graphics;
};

