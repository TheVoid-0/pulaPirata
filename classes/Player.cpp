#include "Player.h"


Player::Player(int hp, int id)
{
	this->hp = hp;
	this->id = id;
	this->swordsUsed = 0;
	this->animating = false;
	this->animationFrames = 0;
	// TODO: instanciar todas as espadas e colocar elas em algum lugar na mesa.
	for(int i=0; i < 8; i++)
	{
		this->swords[i] = Obj("objects/espada.obj", "./objects/textures/Espada_texture.dds");
	}
}

Player::Player()
{
}

void Player::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Light *light, Hole *hole, bool* changeTurn, bool *gameOver)
{
	for (int i = 0; i <= this->swordsUsed; i++)
	{
		
		// TODO: trocar a cor da espada ou fazer qualquer coisa para diferenciar os dois players
		// TODO: Colocar o hp dos jogadores na tela
		if (i == this->swordsUsed) {

			if (this->animating) {
				this->swords[i].translate(glm::vec3(0.001f, 0.0f, 0.0f));
				this->animationFrames++;
				// TODO: colocar o projeto dentro de frames definidos?
				if (hole->isTrap()) {
					this->damagePirate(false, (light + 1));
				}

				if (this->animationFrames == 1500) {
					this->animationFrames = 0;
					this->damagePirate(true, (light + 1));
					hole->setPlayerId(this->id);
					this->swordsUsed++;
					this->animating = false;
					*changeTurn = true;
					if (hole->isTrap()) {
						this->hp--;
					}
					if (hp == 0) {
						// TODO: implementar game over
						*gameOver = true;
					}
				}
			}

			if (!hole->isSwordInPosition()) {
				this->swords[i].resetModelMatrix();
				this->swords[i].translate(hole->getLocation());
				this->swords[i].rotate(hole->getYAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
				this->swords[i].translate(glm::vec3(-1.7f, 0.0f, 0.0f));
				hole->setIsSwordInPosition(true);
			}
		}
		this->swords[i].draw(projectionMatrix, viewMatrix, *light);
	}
}

void Player::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Light light)
{
	for (int i = 0; i <= this->swordsUsed; i++)
	{
		this->swords[i].draw(projectionMatrix, viewMatrix, light);
	}
}

void Player::damagePirate(bool reset, Light* light)
{
	if (reset) {
		light->setColor(1.0f, 1.0f, 1.0f);
		light->setPower(20.0f);
		light->setPosition(4.0f, 4.0f, 4.0f);
	}
	else {
		light->setColor(1.0f, 0.0f, 0.0f);
		light->setPower(80.0f);
		light->setPosition(4.0f, 4.0f, 4.0f);
	}
}

void Player::setAnimating(bool animating)
{
	this->animating = animating;
}

bool Player::isAnimating()
{
	return this->animating;
}
