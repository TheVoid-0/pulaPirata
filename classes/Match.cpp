#include "Match.h"
#include <pula_pirata\programHandler.hpp>
#include <common\text2D.hpp>
#include <time.h>


Match::Match()
{
	this->startGame(false);
}

void Match::setProjectionMatrix(glm::mat4 projectionMatrix)
{
	this->projectionMatrix = projectionMatrix;
}

void Match::setViewMatrix(glm::mat4 viewMatrix)
{
	this->viewMatrix = viewMatrix;
}

glm::mat4 Match::getProjectionMatrix()
{
	return this->projectionMatrix;
}

glm::mat4 Match::getViewMatrix()
{
	return this->viewMatrix;
}


void Match::startGame(bool isRestart)
{
	// seed for rand()
	srand(time(0));
	this->gameOver = false;
	this->turn = 0;
	this->indexSelected = 0;
	this->holesTaken = 0;
	this->players[0] = Player(2, 1);
	this->players[1] = Player(2, 2);
	if (!isRestart) {
		this->barrel = Obj("objects/barril.obj", "./objects/textures/Barril_texture.dds");
		this->table = Obj("objects/mesa.obj", "./objects/textures/Mesa_texture.dds");
		this->pirate = Obj("objects/pirata.obj", "./objects/textures/Pirata_texture.dds");
		this->menu = Obj("objects/Menu.obj", "./objects/textures/Texture_Cubo.dds");
	}
	this->setInitialPosition();
	this->lights[0] = Light(glm::vec3(4, 4, 4), glm::vec3(1, 1, 1), 50.0f);
	this->lights[1] = Light(glm::vec3(4, 4, 4), glm::vec3(1, 1, 1), 20.0f);
	this->lights[2] = Light(glm::vec3(-4, 4, -4), glm::vec3(1, 1, 1), 20.0f);


	this->holes[0] = Hole(glm::vec3(0.60f, -0.3f, 1.2f), 122.0f);
	this->holes[1] = Hole(glm::vec3(1.0f, 0.35f, 0.85f), 145.0f);
	this->holes[2] = Hole(glm::vec3(1.30f, -0.3f, 0.40f), 167.0f);
	this->holes[3] = Hole(glm::vec3(1.2f, 0.35f, -0.1f), 190.0f);
	this->holes[4] = Hole(glm::vec3(1.20f, -0.3f, -0.60f), 212.0f);
	this->holes[5] = Hole(glm::vec3(0.85f, 0.35f, -1.0f), 235.0f);
	this->holes[6] = Hole(glm::vec3(0.40f, -0.3f, -1.20f), 257.0f);
	this->holes[7] = Hole(glm::vec3(-0.10f, 0.35f, -1.25f), 280.0f);
	this->holes[8] = Hole(glm::vec3(-0.60f, -0.3f, -1.15f), 302.0f);
	this->holes[9] = Hole(glm::vec3(-1.00f, 0.35f, -0.85f), 325.0f);
	this->holes[10] = Hole(glm::vec3(-1.3f, -0.3f, -0.40f), 347.0f);
	this->holes[11] = Hole(glm::vec3(-1.2f, 0.35f, 0.1f), 10.0f);
	this->holes[12] = Hole(glm::vec3(-1.25f, -0.3f, 0.65f), 32.0f);
	this->holes[13] = Hole(glm::vec3(-0.8f, 0.35f, 0.95f), 55.0f);
	this->holes[14] = Hole(glm::vec3(-0.35f, -0.3f, 1.15f), 77.0f);
	this->holes[15] = Hole(glm::vec3(0.1f, 0.35f, 1.25f), 100.0f);

	int trapIndices[8];
	this->generateTraps(&trapIndices[0]);
	for (int i = 0; i < 8; i++)
	{
		printf("traps: %d", trapIndices[i]);
		this->holes[trapIndices[i]].setIsTrap(true);
	}
}

void Match::nextHole()
{
	int newIndex = 0;
	for (int i = 1; i < 16; i++)
	{
		newIndex = this->indexSelected + i;
		if (newIndex < 16) {
			if (!this->holes[newIndex].isTaken()) {
				this->holes[this->indexSelected].setIsSwordInPosition(false);
				this->indexSelected = newIndex;
				return;
			}
		}
		else {
			break;
		}
		
	}
	for (int i = 0; i < indexSelected; i++)
	{
		if (!this->holes[i].isTaken()) {
			this->holes[this->indexSelected].setIsSwordInPosition(false);
			this->indexSelected = i;
			return;
		}
	}
}

void Match::previousHole()
{
	int newIndex = 0;
	for (int i = 1; i < 16; i++)
	{
		newIndex = this->indexSelected - i;
		if (newIndex > -1) {
			if (!this->holes[newIndex].isTaken()) {
				this->holes[this->indexSelected].setIsSwordInPosition(false);
				this->indexSelected = newIndex;
				return;
			}
		}
		else {
			break;
		}

	}
	for (int i = 15; i > indexSelected; i--)
	{
		if (!this->holes[i].isTaken()) {
			this->holes[this->indexSelected].setIsSwordInPosition(false);
			this->indexSelected = i;
			return;
		}
	}
}

void Match::selectHole()
{
	if (!this->players[turn].isAnimating()) {
		this->players[turn].setAnimating(true);
	}
	return;
}

void Match::draw()
{
	// Use our shader
	glUseProgram(getProgramId());

	if (this->drawMenu) {
		this->menu.draw(this->projectionMatrix, this->viewMatrix, this->lights[0]);
	}
	else {
		bool changeTurn = false;
		this->table.draw(this->projectionMatrix, this->viewMatrix, this->lights[0]);
		this->barrel.draw();

		// primeiro draw do player tem que ser do player do turno pois a seleção do Hole é de quem chegar primeiro
		this->players[turn].draw(this->projectionMatrix, this->viewMatrix, this->lights,
			&this->holes[this->indexSelected], &changeTurn, &this->gameOver);

		this->pirate.draw(this->projectionMatrix, this->viewMatrix, this->lights[1], getProgramId());

		for (int i = 0; i < 2; i++)
		{
			if (i != turn) {
				this->players[i].draw(this->projectionMatrix, this->viewMatrix, this->lights[0]);
			}
		}

		if (changeTurn) {
			this->turn = this->turn == 0 ? 1 : 0;
			this->nextHole();
		}

		if (this->gameOver) {
			char* message = this->turn == 0 ? "Azul venceu!" : "Rosa venceu!";
			char text[256];
			sprintf(text, "%s", message);
			printText2D(text, 50, 300, 60);
		}
	}

}

void Match::setShouldDrawMenu(bool shouldDrawMenu)
{
	this->drawMenu = shouldDrawMenu;
}

bool Match::shouldDrawMenu()
{
	return this->drawMenu;
}

bool Match::isGameOver()
{
	return this->gameOver;
}

void Match::setInitialPosition()
{
	this->pirate.resetModelMatrix();
	this->menu.resetModelMatrix();
	this->pirate.translate(glm::vec3(0.0f, 2.2f, 0.0f));

	this->menu.translate(glm::vec3(0.0f, 3.5f, 27.0f));
	this->menu.rotate(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Match::nextSelectableHole()
{
	for (int i = 0; i < 16; i++)
	{
		if (!this->holes[i].isTaken()) {
			this->indexSelected = i;
		}
	}
}

void Match::generateTraps(int* output)
{
	int i = 0;
	const int max = 15;
	const int min = 0;
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x;
	do
	{
		do {
			x = rand();
		} while (x >= RAND_MAX - remainder);
		x = min + x % n;
		if (this->isUniqueInArray(x, output)) {
			output[i] = x;
			i++;
		}
	} while (i < 8);
}

bool Match::isUniqueInArray(int numberToTest, int* array)
{
	for (int i = 0; i < 8; i++)
	{
		if (*(array + i) == numberToTest) {
			return false;
		}
	}
	return true;
}
