#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs(bool *shouldDrawMenu);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::mat4 getOrthoProjectionMatrix();

#endif