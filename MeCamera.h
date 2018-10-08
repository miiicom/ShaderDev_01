#pragma once
#include <glm\glm.hpp>
class MeCamera
{
public:
	MeCamera();
	~MeCamera();

	glm::mat4 getWorldToViewMatrix() const;
	void mouseUpdate(const glm::vec2& newMousePosition);

private:
	glm::vec3 position;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
};

