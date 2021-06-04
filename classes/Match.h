#pragma once
#include <common/controls.hpp>

#include <pula_pirata/classes/Player.h>
#include <pula_pirata/classes/Hole.h>
#include <pula_pirata/classes/Obj.h>
#include <pula_pirata/classes/Light.h>
class Match
{
	Hole holes[16];
	Player players[2];
	int turn;
	int indexSelected;
	int holesTaken;
	// TODO: seria melhor o Hole dentro de uma classe Barrel? Traria alguma vantagem? acho que somente se o barril fosse um objeto móvel ou se fossem vários barris,
	// nesse caso tanto faz e é mais prático controlar ele pelo Match
	Obj barrel;
	Obj table;
	Obj pirate;
	Obj menu;
	bool shouldDrawMenu;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	Light lights[2];

	// TODO: verificar para colocar o computeMatrices do controls.hpp dentro do Match em algum lugar, 
	// aí podemos passar qual o buraco em foco e a View e Projection para todos os draws
	void startGame();
	void nextHole();
	void previousHole();
	void selectHole();
	void draw();

private:
	void setInitialPosition();

};

