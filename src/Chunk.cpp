#include <stdlib.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Chunk.h"

Chunk::Chunk(): position(0) {
	fillTerrainPoints();

	BakedChunk bake(points);
	loadModel(bake.getMesh(), bake.getSize());
}

void Chunk::bindModel() {
	glBindVertexArray(vao[0]);
}

void Chunk::render() {
	glDrawArrays(GL_TRIANGLES, 0, vbSize);
}

glm::mat4 Chunk::getTranslationMat() {
	return glm::translate(glm::mat4(), position);
}

void Chunk::fillTerrainPoints() {
//	points[0][0][0] = true;
	points[1][0][0] = true;
	points[1][1][0] = true;
	points[0][1][0] = true;

	points[0][0][1] = true;
	points[1][0][1] = true;
	points[1][1][1] = true;
	points[0][1][1] = true;
}

void Chunk::loadModel(GLfloat *arr, int siz) {
	vbSize = siz;
	glGenBuffers(2, vbo);

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);


	// Positions
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * siz * sizeof(GLfloat), arr, GL_STATIC_DRAW);
	glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttributeIndex);

	// TEMP CODE
	GLfloat colors[siz * floatsPerColor];
	genRandFloats(colors, siz * floatsPerColor);

	// Colors
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, ( siz * floatsPerColor) * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeIndex);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Chunk::genRandFloats(GLfloat* arrLoc, int ammount) {
	for (int i = 0; i < ammount; i++) {
		arrLoc[i] = rand() % 10 / 10.0 + 0.1;
	}
}

void Chunk::setPostition(glm::vec3 pos) {
	position = pos;
}

glm::vec3 Chunk::getPostition() {
	return position;
}


Chunk::~Chunk() {
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}