#include <stdlib.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "Model.h"

Model::Model(float x, float y) {

	for (auto &row : colors) {
		row[0] = (rand() % 500) / 500.0;
		row[1] = (rand() % 500) / 500.0;
		row[2] = (rand() % 500) / 500.0;
	}

	for (auto &row : diamond) {
		row[0] += x;
		row[1] += y;
	}

	loadModel();
}

void Model::loadModel() {
	glGenBuffers(2, vbo);

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);


	// Positions
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, ( points * floatsPerPoint) * sizeof(GLfloat), diamond, GL_STATIC_DRAW);
	glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttributeIndex);

	// Colors
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, ( points * floatsPerColor) * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeIndex);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Model::bindModel() {
	glBindVertexArray(vao[0]);
}


void Model::cleanup() {
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}



Model::~Model() {
	cleanup();
}
