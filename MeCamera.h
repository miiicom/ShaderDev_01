#pragma once
#include <glm\glm.hpp>
class MeCamera
{
public:
	MeCamera();
	~MeCamera();

	glm::mat4 getWorldToViewMatrix() const;
	void mouseUpdate(const glm::vec2& newMousePosition);
	void setViewDirection(glm::vec3 newViewDirection);
	glm::vec3 getViewDirection();
	glm::vec3 getUp();
	glm::vec3 position;
	glm::vec3 viewDirection;
	const glm::vec3 UP;

private:

	
};

