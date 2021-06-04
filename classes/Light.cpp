#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, GLfloat power)
{
	this->position = position;
	this->color = color;
	this->power = power;
}

Light::Light()
{

}
