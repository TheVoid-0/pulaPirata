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
