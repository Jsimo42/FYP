#include "pch.h"
#include "Camera.h"


Camera::Camera(glm::vec3 PositionIn, glm::vec3 DirectionIn, glm::vec3 WorldUpIn)
{
	ViewMatrix = glm::mat4(1.f);
	MoveSpeed = 5.f;
	MouseSensitivity = 5.f;

	WorldUp = WorldUpIn;
	CameraPosition = PositionIn;
	CameraRight = glm::vec3(0.f);
	CameraUp = WorldUpIn;

	Pitch = -25.f;
	Yaw = 180.f;
	Roll = 0.f;
	
	UpdateCameraVectors();
}

void Camera::UpdateInput(const float & DeltaTimeIn, const double & OffsetX, const double & OffsetY)
{
	UpdateMouseInput(DeltaTimeIn, OffsetX, OffsetY);
}

const glm::mat4 Camera::GetViewMatrix()
{
	UpdateCameraVectors();
	
	ViewMatrix = glm::lookAt(CameraPosition, CameraPosition + CameraForward, CameraUp);

	return ViewMatrix;
}

void Camera::MoveCamera(const float & DeltaTimeIn, const EDirection Direction)
{
	switch (Direction)
	{
	case EForward:
		CameraPosition += CameraForward * MoveSpeed * DeltaTimeIn;
		break;
	case EBack:
		CameraPosition -= CameraForward * MoveSpeed * DeltaTimeIn;
		break;
	case ELeft:
		CameraPosition -= CameraRight * MoveSpeed * DeltaTimeIn;
		break;
	case ERight:
		CameraPosition += CameraRight * MoveSpeed * DeltaTimeIn;
		break;
	default:
		break;	
	}
}

void Camera::UpdateCameraVectors()
{
	CameraForward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	CameraForward.y = sin(glm::radians(Pitch));
	CameraForward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	CameraForward = glm::normalize(CameraForward);
	CameraRight = glm::normalize(glm::cross(CameraForward, WorldUp));
	CameraUp = glm::normalize(glm::cross(CameraRight, CameraForward));	
}

void Camera::UpdateMouseInput(const float & DeltaTimeIn, const double & OffsetX, const double & OffsetY)
{
	Pitch += (GLfloat)OffsetY * MouseSensitivity * DeltaTimeIn;
	Yaw += (GLfloat)OffsetX * MouseSensitivity * DeltaTimeIn;

	if (Pitch >= 80.f)
	{
		Pitch = 80.f;
	}
	else if (Pitch <= -80.f)
	{
		Pitch = -80.f;
	}

	if (Yaw > 360.f || Yaw < -360.f)
	{
		Pitch = 0.f;
	}
}
