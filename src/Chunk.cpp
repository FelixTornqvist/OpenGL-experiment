#include <math.h>

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
	int chunk2div2 = CHUNK_SIZE / 2;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				int x2 = x - (CHUNK_SIZE / 2);
				x2 *= x2;
				int y2 =  y - (CHUNK_SIZE / 2);
				y2 *= y2;
				int z2 =  z - (CHUNK_SIZE / 2);
				z2 *= z2;

                points[x][y][z] = sqrt(x2 + y2 + z2) < chunk2div2;
			}
		}
	}
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
