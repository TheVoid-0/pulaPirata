#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <vector>
#include <GL\glew.h>

#include <pula_pirata/classes/Light.h>

class Obj
{
protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	// Por questões de praticidade cada objeto vai ficar limitado a somente uma textura;
	GLuint texture;
	glm::mat4 modelMatrix;
	// Por questões de teste vamos usar um buffer para cada objeto que guardará o conteúdo daquele objeto até o fim
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;

public:
	Obj(char *objFilePath, char *ddsTexturePath);
	void draw();
	void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Light light);
	void translate(glm::vec3 xyz);
	void rotate(GLfloat angle, glm::vec3 xyz);
	//void scale();
	void resetModelMatrix();
};
