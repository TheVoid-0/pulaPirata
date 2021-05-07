// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>


// TODO: fazer função inicializar os buffers e setar seus atributos apenas uma vez
// TODO: separar o código em classes com propriedades de cada objeto

void draw(GLuint vertexbuffer, GLuint uvbuffer, GLuint normalbuffer, std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals) {
	// Load it into a VBO
	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//glGenBuffers(1, &uvbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	//glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 07 - Model Loading", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	//GLuint Texture = loadDDS("uvmap.DDS");
	GLuint Texture = loadDDS("./objects/textures/Mesa_texture.dds");
	GLuint TextureEspada = loadDDS("./objects/textures/EspadaAzul.dds");
	GLuint TextureBarril = loadDDS("./objects/textures/Barril_texture.dds");
	GLuint TexturePirata = loadDDS("./objects/textures/Pirata_texture.dds");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// BARRIL
	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("objects/barril.obj", vertices, uvs, normals);
	
	// Load it into a VBO
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	// ESPADA
	std::vector<glm::vec3> verticesEspada;
	std::vector<glm::vec2> uvsEspada;
	std::vector<glm::vec3> normalsEspada;
	bool resEspada = loadOBJ("objects/espada.obj", verticesEspada, uvsEspada, normalsEspada);
	
	// Load it into a VBO
	GLuint vertexbufferEspada;
	glGenBuffers(1, &vertexbufferEspada);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferEspada);
	glBufferData(GL_ARRAY_BUFFER, verticesEspada.size() * sizeof(glm::vec3), &verticesEspada[0], GL_STATIC_DRAW);

	GLuint uvbufferEspada;
	glGenBuffers(1, &uvbufferEspada);
	glBindBuffer(GL_ARRAY_BUFFER, uvbufferEspada);
	glBufferData(GL_ARRAY_BUFFER, uvsEspada.size() * sizeof(glm::vec2), &uvsEspada[0], GL_STATIC_DRAW);

	// PIRATA
	std::vector<glm::vec3> verticesPirata;
	std::vector<glm::vec2> uvsPirata;
	std::vector<glm::vec3> normalsPirata;
	bool resPirata = loadOBJ("objects/pirata.obj", verticesPirata, uvsPirata, normalsPirata);

	// Load it into a VBO
	GLuint vertexbufferPirata;
	glGenBuffers(1, &vertexbufferPirata);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferPirata);
	glBufferData(GL_ARRAY_BUFFER, verticesPirata.size() * sizeof(glm::vec3), &verticesPirata[0], GL_STATIC_DRAW);

	GLuint uvbufferPirata;
	glGenBuffers(1, &uvbufferPirata);
	glBindBuffer(GL_ARRAY_BUFFER, uvbufferPirata);
	glBufferData(GL_ARRAY_BUFFER, uvsPirata.size() * sizeof(glm::vec2), &uvsPirata[0], GL_STATIC_DRAW);

	// MESA
	std::vector<glm::vec3> verticesMesa;
	std::vector<glm::vec2> uvsMesa;
	std::vector<glm::vec3> normalsMesa;
	bool resMesa = loadOBJ("objects/mesa.obj", verticesMesa, uvsMesa, normalsMesa);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		// Cria uma posição para a luz e envia aos shaders
		glm::vec3 lightPos = glm::vec3(4, 4, 4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);

		draw(vertexbuffer, uvbuffer, normalbuffer, verticesMesa, uvsMesa, normalsMesa);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureBarril);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		draw(vertexbuffer, uvbuffer, normalbuffer, vertices, uvs, normals);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureEspada);

		// BUT the Model matrix is different (and the MVP too)
		glm::mat4 ModelMatrix2 = glm::mat4(1.0);
		ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(-1.3f, 0.0f, 0.0f));
		//ModelMatrix2 = glm::rotate(ModelMatrix2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 1.0f));
		glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);

		draw(vertexbuffer, uvbuffer, normalbuffer, verticesEspada, uvsEspada, normalsEspada);

		
		glm::mat4 ModelMatrix3 = glm::mat4(1.0);
		ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(0.0f, 2.2f, 0.0f));
		glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexturePirata);

		draw(vertexbuffer, uvbuffer, normalbuffer, verticesPirata, uvsPirata, normalsPirata);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

