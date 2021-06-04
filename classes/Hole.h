#pragma once
#include <glm/glm.hpp>
#include <GL\glew.h>
class Hole
{
private:
	glm::vec3 xyz;
	GLfloat yAngle;
	int playerId; // 0 = null
	bool trap;

public:
	void setLocation(glm::vec3 xyz, GLfloat yAngle);
	void setPlayerId(int playerId);
	void setIsTrap(bool isTrap);
	bool isTrap();
	bool isTaken();
	glm::vec3 getLocation();
	GLfloat getYAngle();
};

