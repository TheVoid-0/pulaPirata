#include "Hole.h"

Hole::Hole()
{
}

Hole::Hole(glm::vec3 locationXyz, GLfloat yAngle)
{
	this->xyz = locationXyz;
	this->yAngle = yAngle;
	this->swordInPosition = false;
	this->playerId = 0;
	this->trap = false;
}

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

bool Hole::isSwordInPosition()
{
	return this->swordInPosition;
}

void Hole::setIsSwordInPosition(bool isSwordInPoisition)
{
	this->swordInPosition = isSwordInPoisition;
}

glm::vec3 Hole::getLocation()
{
	return this->xyz;
}

GLfloat Hole::getYAngle()
{
	return this->yAngle;
}
