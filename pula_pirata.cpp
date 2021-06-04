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

#include <pula_pirata/programHandler.hpp>
#include <pula_pirata/classes/Obj.h>
#include <pula_pirata/classes/Light.h>

#include <pula_pirata/classes/Match.h>


// TODO: fazer fun��o inicializar os buffers e setar seus atributos apenas uma vez ou trocar os dados e sempre utilizar o mesmo buffer (estou tentando com um buffer para cada objeto)
// TODO: separar o c�digo em classes com propriedades de cada objeto (estou tentando)
// TODO: deletar todos os buffers e liberar as texturas da mem�ria (N�o � prioridade, funciona de qualquer jeito, s� seria o mais correto)

void draw(GLuint vertexbuffer, GLuint uvbuffer, GLuint normalbuffer, std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals) {

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

	programHandler();

	Match match;

	// OBJETOS
	//Obj mesa("objects/mesa.obj", "./objects/textures/Mesa_texture.dds");
	//Obj espada("objects/espada.obj","./objects/textures/Espada_texture.dds");
	//Obj barril("objects/barril.obj","./objects/textures/Barril_texture.dds");
	//Obj pirata("objects/pirata.obj","./objects/textures/Pirata_texture.dds");
	//Obj menu("objects/Menu.obj","./objects/textures/Texture_Cubo.dds");

	//float x = -1.25f;
	//float y = -0.3f;
	//float z = 0.65f;

	//espada.translate(glm::vec3(x, y, z));
	//espada.rotate(-5.0f, glm::vec3(0.0f, 1.0f, 1.0f));
	//espada.rotate(32.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	//pirata.translate(glm::vec3(0.0f, 2.2f, 0.0f));

	//menu.translate(glm::vec3(0.0f, 3.5f, 27.0f));
	//menu.rotate(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	// LUZES
	//Light luzAmbiente(glm::vec3(4, 4, 4), glm::vec3(1, 1, 1), 50.0f);
	//Light luzPirata(glm::vec3(4, 4, -4), glm::vec3(0.5, 0.5, 0), 50.0f);

	//float novoX = 0.0f;
	//bool entra = false;

	// decide se deve renderizar o Menu ou n�o
	bool shouldDrawMenu = true;
	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(getProgramId());

		//computeMatricesFromInputs(&shouldDrawMenu);
		//glm::mat4 ProjectionMatrix = getProjectionMatrix();
		//glm::mat4 ViewMatrix = getViewMatrix();
		match.draw();
		//mesa.draw(ProjectionMatrix, ViewMatrix, luzAmbiente);
		//barril.draw();
		//espada.draw(ProjectionMatrix, ViewMatrix, luzAmbiente);


		//if (!entra) {
		//	novoX -= 0.001;
			//printf("%f\n", novoX);

			//espada.translate(glm::vec3(novoX, 0.0f, 0.0f));

//			if (novoX < -0.05) {
	//			entra = true;
		//		novoX = 0.0;
			//}
		//}
		//else {
			//novoX += 0.001;
			//printf("%f\n", novoX);

			//espada.translate(glm::vec3(novoX, 0.0f, 0.0f));

			//if (novoX >= 0.05) {
			//	entra = false;
			//	novoX = 0.0;
			//}
	//	}
		
		// PIRATA
		//pirata.draw(ProjectionMatrix, ViewMatrix, luzPirata);

//		if (shouldDrawMenu) {
	//		menu.draw(ProjectionMatrix, ViewMatrix, luzAmbiente);
		//}

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
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteBuffers(1, &uvbuffer);
	//glDeleteProgram(programID);
	//glDeleteTextures(1, &Texture);
	//glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

