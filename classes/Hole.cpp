#include "Hole.h"

void Hole::setLocation(glm::vec3 xyz, GLfloat yAngle)
{
	this->xyz = xyz;
	this->yAngle = yAngle;
}

void Hole::setPlayerId(int playerId)
{
	this->playerId = playerId;
}

void Hole::setIsTrap(bool isTrap)
{
	this->trap = isTrap;
}

bool Hole::isTrap()
{
	return this->trap;
}

bool Hole::isTaken()
{
	if (!this->playerId || this->playerId == 0) {
		return false;
	}
	return true;
}

glm::vec3 Hole::getLocation()
{
	return this->xyz;
}

GLfloat Hole::getYAngle()
{
	return this->yAngle;
}
