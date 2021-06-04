#include "Match.h"


Match::Match()
{
	this->startGame();
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


void Match::startGame()
{
	this->turn = 0;
	this->holesTaken = 0;
	this->players[0] = Player(1, 1);
	this->players[1] = Player(1, 2);
	this->barrel = Obj("objects/barril.obj", "./objects/textures/Barril_texture.dds");
	this->table = Obj("objects/mesa.obj", "./objects/textures/Mesa_texture.dds");
	this->pirate = Obj("objects/pirata.obj", "./objects/textures/Pirata_texture.dds");
	this->menu = Obj("objects/Menu.obj", "./objects/textures/Texture_Cubo.dds");
	this->setInitialPosition();
	this->lights[0] = Light(glm::vec3(4, 4, 4), glm::vec3(1, 1, 1), 50.0f);
	this->lights[1] = Light(glm::vec3(4, 4, -4), glm::vec3(0.5, 0.5, 0), 50.0f);

	this->holes[0].setLocation(glm::vec3(-1.2f, 0.35f, 0.1f), 10.0f);
	this->holes[1].setLocation(glm::vec3(-1.25f, -0.3f, 0.65f), 32.0f);
	this->holes[2].setLocation(glm::vec3(-0.8f, 0.35f, 0.95f), 55.0f);
	this->holes[3].setLocation(glm::vec3(-0.35f, -0.3f, 1.15f), 77.0f);
	this->holes[4].setLocation(glm::vec3(0.1f, 0.35f, 1.25f), 100.0f);
	this->holes[5].setLocation(glm::vec3(0.60f, -0.3f, 1.2f), 122.0f);
	this->holes[6].setLocation(glm::vec3(1.0f, 0.35f, 0.85f), 145.0f);
	this->holes[7].setLocation(glm::vec3(1.30f, -0.3f, 0.40f), 167.0f);
	this->holes[8].setLocation(glm::vec3(1.2f, 0.35f, -0.1f), 190.0f);
	this->holes[9].setLocation(glm::vec3(1.20f, -0.3f, -0.60f), 212.0f);
	this->holes[10].setLocation(glm::vec3(0.85f, 0.35f, -1.0f), 235.0f);
	this->holes[11].setLocation(glm::vec3(0.40f, -0.3f, -1.20f), 257.0f);
	this->holes[12].setLocation(glm::vec3(-0.10f, 0.35f, -1.25f), 280.0f);
	this->holes[13].setLocation(glm::vec3(-0.60f, -0.3f, -1.15f), 302.0f);
	this->holes[14].setLocation(glm::vec3(-1.00f, 0.35f, -0.85f), 325.0f);
	this->holes[15].setLocation(glm::vec3(-1.3f, -0.3f, -0.40f), 347.0f);

	// TODO: colocar a localização de cada buraco manualmente :(
	// sem a construção dos holes[] o programa vai crashar
	// e decidir se será uma trap ou não
}

void Match::nextHole()
{
	int newIndex = 0;
	for (int i = 1; i < 16; i++)
	{
		newIndex = this->indexSelected + i;
		if (newIndex < 16) {
			if (!this->holes[newIndex].isTaken()) {
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
			this->indexSelected = i;
			return;
		}
	}
}

void Match::selectHole()
{
	// TODO: adicionar lógica para selecionar o buraco, realizar a animação de inserção da espada, marcar o buraco como escolhido pelo jogador do turno e passar o turno;
	return;
}

void Match::draw()
{
	// TODO: colocar os comandos de mexer/selecionar e escolher um buraco no controls.cpp
	// TODO: passar o computeMatrices para fora e passar uma instancia do Match como parâmetro para poder chamar os métodos de controle?
	//computeMatricesFromInputs(&this->shouldDrawMenu);
	//this->projectionMatrix = getProjectionMatrix();
	//this->viewMatrix = getViewMatrix();

	this->table.draw(this->projectionMatrix, this->viewMatrix, this->lights[0]);
	this->barrel.draw();
	this->pirate.draw(this->projectionMatrix, this->viewMatrix, this->lights[1]);

	for each (Player player in this->players)
	{
		//player.draw(this->projectionMatrix, this->viewMatrix, this->lights[0], this->holes[this->indexSelected]);
	}

	if (this->drawMenu) {
		this->menu.draw(this->projectionMatrix, this->viewMatrix, this->lights[0]);
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

void Match::setInitialPosition()
{
	this->pirate.translate(glm::vec3(0.0f, 2.2f, 0.0f));

	this->menu.translate(glm::vec3(0.0f, 3.5f, 27.0f));
	this->menu.rotate(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}
