#pragma once
#include <glm\glm.hpp>
class Camera
{
 
	glm::vec3 viewDirection;
	const glm::vec3 UP;
	glm::vec2 oldMousePosition;
	static const float MOVEMENT_SPEED;// = 0.1f;
	glm::vec3 strafeDirection;
public:
	Camera();
	void mouseUpdate(const glm::vec2 &newMousePosition);
	glm::mat4 getWorldToViewMatrix() const;
	void moveForward();
	void moveBackwards();
	void strafeLeft();
	void strafeRight();
	void moveUp();
	void moveDown();
	glm::vec3 position;
};

