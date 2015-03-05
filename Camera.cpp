#include "Camera.h"
#include <glm\gtx\transform.hpp>

Camera::Camera() : viewDirection(0.0f,0.0f, -1.0f),
UP(0.0f, 1.0f, 0.0f) 
{
}

void Camera::mouseUpdate(const glm::vec2 &newMousePosition)
{	
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 40.0f)
	{
		oldMousePosition = newMousePosition;
		return;
	}
	//mouseDelta.x
	const float ROTATIONAL_SPEED = 0.5f;
	viewDirection = glm::mat3(glm::rotate(-mouseDelta.x * ROTATIONAL_SPEED, UP)) * viewDirection;
	glm::vec3 toRotateAround = glm::cross(viewDirection, UP);
	viewDirection = glm::mat3(glm::rotate(-mouseDelta.y * ROTATIONAL_SPEED, toRotateAround)) * viewDirection;
	oldMousePosition = newMousePosition;
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}
