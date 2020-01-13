#pragma once

#include "Libs.h"
#include "GraphicsEngine.h"

class Entity
{
public:
	Entity(EEntityType EntityType, glm::vec3 PositionIn, glm::vec3 RotatonIn, glm::vec3 ScaleIn);
	~Entity();

	void Render(GraphicsEngine* Graphics);

private:
	EEntityType Type = EEntityType::ENone;
	
};

