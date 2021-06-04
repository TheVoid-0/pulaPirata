#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <GL\glew.h>
class Light
{
public:
	glm::vec3 position;
	glm::vec3 color;
	GLfloat power;
	
	Light();
	Light(glm::vec3 position, glm::vec3 color, GLfloat power);
};

