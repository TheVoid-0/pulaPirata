#pragma once

#include <glm/glm.hpp>
#include <vector>

#include <pula_pirata/classes/Player.h>
#include <pula_pirata/classes/Hole.h>
#include <pula_pirata/classes/Obj.h>
#include <pula_pirata/classes/Light.h>
class Match
{
private:
	Hole holes[16];
	Player players[2];
	int turn;
	int indexSelected;
	int holesTaken;
	// seria melhor o Hole dentro de uma classe Barrel? Traria alguma vantagem? acho que somente se o barril fosse um objeto móvel ou se fossem vários barris,
	// nesse caso tanto faz e é mais prático controlar ele pelo Match
	Obj barrel;
	Obj table;
	Obj pirate;
	Obj menu;
	bool drawMenu;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	Light lights[2];

	void setInitialPosition();

public:
	Match();
	void setProjectionMatrix(glm::mat4 projectionMatrix);
	void setViewMatrix(glm::mat4 viewMatrix);
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	void startGame();
	void nextHole();
	void previousHole();
	void selectHole();
	void draw();
	void setShouldDrawMenu(bool shouldDrawMenu);
	bool shouldDrawMenu();

};

