#include "pch.h"
#include "Entity.h"


Entity::Entity(EEntityType EntityType, glm::vec3 PositionIn, glm::vec3 RotatonIn, glm::vec3 ScaleIn)
{
}

Entity::~Entity()
{
}

void Entity::Render(GraphicsEngine * Graphics)
{
	GraphicsEngine->Render();
}
