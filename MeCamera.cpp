#include "MeCamera.h"
#include <glm\gtx\transform.hpp>


MeCamera::MeCamera() : UP(0.0f,1.0f,0.0f)
{
	viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}


MeCamera::~MeCamera()
{
}

glm::mat4 MeCamera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}

void MeCamera::mouseUpdate(const glm::vec2 & newMousePosition)
{
	viewDirection = glm::mat3(glm::rotate(newMousePosition.x, UP)) *viewDirection;

	glm::vec3 toRotateAround = glm::cross(viewDirection, UP);
	viewDirection = glm::mat3(glm::rotate(newMousePosition.y, toRotateAround)) * viewDirection;
}

void MeCamera::setViewDirection(glm::vec3 newViewDirection)
{
	viewDirection = newViewDirection;
}

glm::vec3 MeCamera::getViewDirection()
{
	return viewDirection;
}

glm::vec3 MeCamera::getUp()
{
	return UP;
}

