#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <pula_pirata/classes/Match.h>
void computeMatricesFromInputs(Match *match);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::mat4 getOrthoProjectionMatrix();

#endif