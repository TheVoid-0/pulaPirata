#include "ProgramHandler.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <common/shader.hpp>

GLuint programID;
GLuint MatrixID;
GLuint ViewMatrixID;
GLuint ModelMatrixID;
GLuint TextureID;
GLuint LightID;
GLuint LightColorID;
GLuint LightPowerID;

void programHandler()
{
	programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");
	TextureID = glGetUniformLocation(programID, "myTextureSampler");
	glUseProgram(programID);
	LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	LightColorID = glGetUniformLocation(programID, "LightColor");
	LightPowerID = glGetUniformLocation(programID, "LightPower");
}

GLuint getMatrixId()
{
	return MatrixID;
}

GLuint getProgramId()
{
	return programID;
}

GLuint getViewMatrixId()
{
	return ViewMatrixID;
}

GLuint getModelMatrixID()
{
	return ModelMatrixID;
}

GLuint getTextureID()
{
	return TextureID;
}

GLuint getLightID()
{
	return LightID;
}

GLuint getLightColorID()
{
	return LightColorID;
}

GLuint getLightPowerID()
{
	return LightPowerID;
}
