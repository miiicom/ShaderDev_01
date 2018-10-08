#pragma once
#include <glm\glm.hpp>
class MeCamera
{
public:
	MeCamera();
	~MeCamera();

	glm::mat4 getWorldToViewMatrix() const;

private:
	glm::vec3 position;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
};

