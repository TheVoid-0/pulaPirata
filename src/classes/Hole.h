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
	bool swordInPosition;

public:
	Hole();
	Hole(glm::vec3 locationXyz, GLfloat yAngle);
	void setLocation(glm::vec3 xyz, GLfloat yAngle);
	void setPlayerId(int playerId);
	void setIsTrap(bool isTrap);
	bool isTrap();
	bool isTaken();
	bool isSwordInPosition();
	void setIsSwordInPosition(bool isSwordInPoisition);
	glm::vec3 getLocation();
	GLfloat getYAngle();
};

