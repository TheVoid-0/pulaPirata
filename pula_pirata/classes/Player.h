#pragma once
#include <pula_pirata/classes/Obj.h>
#include <pula_pirata/classes/Hole.h>
class Player
{
private:
	int id;
	int hp;
	Obj swords[8];
	int swordsUsed;
	bool animating;
	int animationFrames;

public:
	Player(int hp, int id);
	Player();
	void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Light *light, Hole *hole, bool *changeTurn, bool *gameOver);
	void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Light light);
	void damagePirate(bool reset, Light *light);
	void setAnimating(bool animating);
	bool isAnimating();
	void showHp();
};

