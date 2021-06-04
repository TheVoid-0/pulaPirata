#include "Obj.h"
#include <iostream>
#include <common/objloader.hpp>
#include <common\texture.hpp>
#include <pula_pirata/programHandler.hpp>

Obj::Obj(char *objFilePath, char *ddsTexturePath)
{
	if (loadOBJ(objFilePath, this->vertices, this->uvs, this->normals)) {
		glGenBuffers(1, &this->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &this->uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

		glGenBuffers(1, &this->normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);

		this->texture = loadDDS(ddsTexturePath);

		this->modelMatrix = glm::mat4(1.0);
	}
	else {
		std::cout << "Não foi possível carregar o objeto em " << objFilePath << " ou não foi possível carregar a textura em " << ddsTexturePath;
	}
}

void Obj::draw()
{
	// Um draw somente a partir dos vertices e a textura, utilizando os uniforms que já estão "bindados" no shader (se algum tiver sido)
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	//glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	//glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	//glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
}

void Obj::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Light light)
{
	glm::mat4 MVP = projectionMatrix * viewMatrix * this->modelMatrix;

	glUniform3f(getLightID(), light.position.x, light.position.y, light.position.z);
	glUniform3f(getLightColorID(), light.color.x, light.color.y, light.color.z);
	glUniform1f(getLightPowerID(), light.power);

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(getMatrixId(), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(getModelMatrixID(), 1, GL_FALSE, &this->modelMatrix[0][0]);
	glUniformMatrix4fv(getViewMatrixId(), 1, GL_FALSE, &viewMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	//glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	//glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	//glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
}

void Obj::translate(glm::vec3 xyz)
{
	this->modelMatrix = glm::translate(this->modelMatrix, xyz);
}

void Obj::rotate(GLfloat angle, glm::vec3 xyz)
{
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(angle), xyz);
}

void Obj::resetModelMatrix()
{
	this->modelMatrix = glm::mat4(1.0f);
}
