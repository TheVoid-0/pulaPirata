#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, GLfloat power)
{
	this->position = position;
	this->color = color;
	this->power = power;
}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->position = glm::vec3(x, y, z);
}

void Light::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->color = glm::vec3(r, g, b);
}

void Light::setPower(GLfloat power)
{
	this -> power = power;
}

Light::Light()
{

}
