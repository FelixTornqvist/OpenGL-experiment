#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"

Model::Model(glm::vec3 pos) {

	std::cout << "constructing model" << std::endl;
	for (auto &row : colors) {
		row[0] = (rand() % 500) / 500.0;
		row[1] = (rand() % 500) / 500.0;
		row[2] = (rand() % 500) / 500.0;
	}

	position = pos;

	std::cout << "loading model" << std::endl;
	loadModel();
	std::cout << "loadED model" << std::endl;
}

void Model::loadModel() {
	std::cout << "1" << std::endl;
	glGenBuffers(2, vbo);
	std::cout << "2" << std::endl;

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	std::cout << "3" << std::endl;

	// Positions
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(
		GL_ARRAY_BUFFER, 
		(points * floatsPerPoint) * sizeof(GLfloat),
		diamond, 
		GL_STATIC_DRAW
	);
	std::cout << "4" << std::endl;
	glVertexAttribPointer(
		positionAttributeIndex, 
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);
	glEnableVertexAttribArray(positionAttributeIndex);

	std::cout << "5" << std::endl;
	// Colors
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(
		GL_ARRAY_BUFFER,
		(points * floatsPerColor) * sizeof(GLfloat),
		colors,
		GL_STATIC_DRAW
	);
	std::cout << "6" << std::endl;
	glVertexAttribPointer(
		colorAttributeIndex,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);
	std::cout << "7" << std::endl;
	glEnableVertexAttribArray(colorAttributeIndex);

	std::cout << "8" << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::bindModel() {
	glBindVertexArray(vao[0]);
}

glm::mat4 Model::getTranslationMat() {
	return glm::translate(glm::mat4(), position);
}

void Model::setPostition(glm::vec3 pos) {
	position = pos;
}

void Model::setRotation(glm::vec3 rot) {
	rotation = rot;
}

void Model::setScale(glm::vec3 scle) {
	scale = scle;
}

void Model::addPostition(glm::vec3 pos) {
	position += pos;
}

void Model::addRotation(glm::vec3 rot) {
	rotation += rot;
}

void Model::addScale(glm::vec3 scle) {
	scale += scle;
}


glm::vec3 Model::getPostition() {
	return position;
}

glm::vec3 Model::getRotation() {
	return rotation;
}

glm::vec3 Model::getScale() {
	return scale;
}



Model::~Model() {
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}
