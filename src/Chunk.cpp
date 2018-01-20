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

glm::mat4 Chunk::getTranslationMat() {
	return glm::translate(glm::mat4(), position);
}

void Chunk::fillTerrainPoints() {
	points[0][0][0] = true;
	points[1][0][0] = true;
	points[1][1][0] = true;
	points[0][1][0] = true;

	points[0][0][1] = true;
	points[1][0][1] = true;
	points[1][1][1] = true;
	points[0][1][1] = true;
}

void Chunk::loadModel(uint *arr, int siz) {
	glGenBuffers(1, vbo);

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);


	// Positions
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, siz * sizeof(uint), arr, GL_STATIC_DRAW);
	glVertexAttribPointer(positionAttributeIndex, 1, GL_INT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttributeIndex);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
