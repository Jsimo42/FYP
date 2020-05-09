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

	glm::vec3 GetScale() { return EntityTransform.Scale; }

	void Move(glm::vec3 MoveAmount) { EntityTransform.Position += MoveAmount; };
	void Rotate(glm::vec3 RotationAmount) { EntityTransform.Rotation += RotationAmount; };
	void Scale(glm::vec3 ScaleAmount) { EntityTransform.Scale += ScaleAmount; };

protected:
	EEntityType Type = EEntityType::ENone;
	std::string FileName{ "" };

	Transform EntityTransform = Transform();
	bool bMesh{ true };

	Material* MeshMaterial = nullptr;
};

