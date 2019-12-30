#pragma once

#include "Libs.h"

class Camera
{
public:
	Camera(glm::vec3 PositionIn, glm::vec3 DirectionIn, glm::vec3 WorldUpIn);

	void UpdateInput(const float& DeltaTimeIn, const int Direction, const double& OffsetX, const double& OffsetY);

	const glm::mat4 GetViewMatrix();
	const glm::vec3 GetCameraPosition() { return CameraPosition; };

	void MoveCamera(const float& DeltaTimeIn, const int Direction);

private:
	GLfloat MoveSpeed{ 0 };
	GLfloat MouseSensitivity{ 0 };

	GLfloat Pitch{ 0 };
	GLfloat Roll{ 0 };
	GLfloat Yaw{ 0 };

	glm::vec3 WorldUp;
	glm::vec3 CameraPosition;
	glm::vec3 CameraForward;
	glm::vec3 CameraRight;
	glm::vec3 CameraUp;

	glm::mat4 ViewMatrix;

	void UpdateCameraVectors();
	void UpdateMouseInput(const float& DeltaTimeIn, const double& OffsetX, const double& OffsetY);
};

