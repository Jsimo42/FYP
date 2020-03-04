#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"

class Entity
{
public:
	Entity(EEntityType EntityType, Transform TransformIn, Material* MaterialIn, std::string FileNameIn = "");
	~Entity();

	virtual void Initialise(GraphicsEngine* Graphics) {};

	virtual Model* GetModel() const { return new Model(); };
	virtual Mesh* GetMesh() const { return new Mesh(); };

	Material* GetMaterial() const { return MeshMaterial; };
	EEntityType GetEntityType() const { return Type; };

protected:
	EEntityType Type = EEntityType::ENone;

	Transform EntityTransform = Transform();
	bool bMesh{ true };

	Material* MeshMaterial = nullptr;
};

