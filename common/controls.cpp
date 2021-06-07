// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 OrthoProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

glm::mat4 getOrthoProjectionMatrix() {
	return OrthoProjectionMatrix;
}

// CAMERA 1
// Initial position : on +Z
glm::vec3 position = glm::vec3( 20, 6, 0 ); 
// Initial horizontal angle : toward -Z
float horizontalAngle = -3.14f/2.0f;
// Initial vertical angle : none
float verticalAngle = -20.0f * 3.14f / 180.0f;
// Initial Field of View
float initialFoV = 45.0f;

// CAMERA 2
glm::vec3 position2 = glm::vec3(-20, 6, 0);
float horizontalAngle2 = 3.14f / 2.0f;
float verticalAngle2 = -20.0f * 3.14f / 180.0f;
float initialFoV2 = 45.0f;

// CAMERA 3
glm::vec3 position3 = glm::vec3(0, 25, 0);
float horizontalAngle3 = -3.14f/2.0f;
float verticalAngle3 = -90.0f * 3.14f / 180.0f;
float initialFoV3 = 45.0f;

// CAMERA 4
glm::vec3 position4 = glm::vec3(0, 5, 30);
float horizontalAngle4 = 3.14f;
float verticalAngle4 = -10.0f * 3.14f / 180.0f;
float initialFoV4 = 45.0f;

// CAMERA MENU
glm::vec3 positionMenu = glm::vec3(0, 5, 43.5);
float horizontalAngleMenu = 3.14f;
float verticalAngleMenu = 0.0f * 3.14f / 180.0f;
float initialFoVMenu = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

bool swapProjectionFlag = true;
int camera = 5; // 1, 2, 3, 4 ou 5

// TODO: refatorar esse código veio para um de verdade com objetos para a entrega final

void calculateProjectionAndViewMatrices(glm::vec3 *position, float *horizontalAngle, float *verticalAngle, float *initialFoV, float *deltaTime, Match *match ){
	
	

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Compute new orientation
	if (!match->shouldDrawMenu()) {
		*horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
		*verticalAngle += mouseSpeed * float(768 / 2 - ypos);
	}
	
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(*verticalAngle) * sin(*horizontalAngle),
		sin(*verticalAngle),
		cos(*verticalAngle) * cos(*horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(*horizontalAngle - 3.14f / 2.0f),
		0,
		cos(*horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {

		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE) {
			camera = 1;
		}
	}

	if (match->isGameOver()) {
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
			camera = 1;
			match->startGame(true);
		}
	}

	if (!match->shouldDrawMenu() && !match->isGameOver()) {
		// Move forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			*position += direction * *deltaTime * speed;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			*position -= direction * *deltaTime * speed;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			*position += right * *deltaTime * speed;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			*position -= right * *deltaTime * speed;
		}
		// change projection
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) {
				swapProjectionFlag = !swapProjectionFlag;
			}
		}
		// zoom in
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			*initialFoV -= *initialFoV * *deltaTime;
		}
		// zoom out
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			*initialFoV += *initialFoV * *deltaTime;
		}

		// change cameras
		if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE) {
				camera = 1;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_RELEASE) {
				camera = 2;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_RELEASE) {
				camera = 3;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
				camera = 4;
			}
		}
		// GAMEPLAY CONTROLS
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
				match->previousHole();
			}
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
				match->nextHole();
			}
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
				match->selectHole();
			}
		}
	}

	

	float FoV = *initialFoV;

	if (swapProjectionFlag) {
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	}
	else {
		float min = -pow(10, glm::radians(FoV));
		float max = pow(10, glm::radians(FoV));
		//OrthoProjectionMatrix = glm::ortho(20.0f, -20.0f, -20.0f, 20.0f, 15.0f, -15.0f);
		ProjectionMatrix = glm::ortho(min, max, min, max, -1000.0f, 1000.0f);
	}

	if (camera == 4) {
		// animacao
			const float radius = 30.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
			ViewMatrix = glm::lookAt(
				glm::vec3(camX, 5.0, camZ),
				glm::vec3(0.0, 0.0, 0.0),
				glm::vec3(0.0, 1.0, 0.0)
			);
	}
	else {
		// Camera matrix
		ViewMatrix = glm::lookAt(
			*position,           // Camera is here
			*position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}
	match->setProjectionMatrix(ProjectionMatrix);
	match->setViewMatrix(ViewMatrix);
}

void computeMatricesFromInputs(Match *match){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	
	// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// GERENCIAMENTO DOS CALCULOS PARA RETORNAR UMA CAMERA DIFERENTE
	switch (camera)
	{
	case 1:
		match->setShouldDrawMenu(false);
		calculateProjectionAndViewMatrices(&position, &horizontalAngle, &verticalAngle, &initialFoV, &deltaTime, match);
		break;
	case 2:
		match->setShouldDrawMenu(false);
		calculateProjectionAndViewMatrices(&position2, &horizontalAngle2, &verticalAngle2, &initialFoV2, &deltaTime, match);
		break;
	case 3:
		match->setShouldDrawMenu(false);
		calculateProjectionAndViewMatrices(&position3, &horizontalAngle3, &verticalAngle3, &initialFoV3, &deltaTime, match);
		break;
	case 4:
		match->setShouldDrawMenu(false);
		calculateProjectionAndViewMatrices(&position4, &horizontalAngle4, &verticalAngle4, &initialFoV4, &deltaTime, match);
		break;
	case 5:
		match->setShouldDrawMenu(true);
		calculateProjectionAndViewMatrices(&positionMenu, &horizontalAngleMenu, &verticalAngleMenu, &initialFoVMenu, &deltaTime, match);
		break;
	default:
		break;
	}

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}