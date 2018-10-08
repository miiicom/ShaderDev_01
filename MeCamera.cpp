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

}
