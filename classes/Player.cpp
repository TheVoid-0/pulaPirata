#include "Player.h"

Player::Player(int hp, int id)
{
	this->hp = hp;
	this->id = id;
	this->swordsUsed = 0;

}

void Player::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Light light, Hole hole)
{
	for (int i = 0; i <= this->swordsUsed; i++)
	{
		
		// TODO: trocar a cor da espada ou fazer qualquer coisa para diferenciar os dois players
		// TODO: Colocar o hp dos jogadores na tela
		if (i == this->swordsUsed) {
			// TODO: colocar ela na posição correta de acordo com o buraco escolhido
			this->swords[i].translate(hole.getLocation());
			this->swords[i].rotate(hole.getYAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
			this->swords[i].draw(projectionMatrix, viewMatrix, light);
		}
		else {
			this->swords[i].draw(projectionMatrix, viewMatrix, light);
		}
	}
}
