#include "BakedChunk.h"

BakedChunk::BakedChunk(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
	bake(points);
}

void BakedChunk::bake(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {

	for (int j = 0; j < 50; j += 1) {
		for (int i = 0; i < 50; i += 1) {
			int x = j, y = i, z = 0;

			point(0 + x,0 + y,0 + z);
			point(0 + x,1 + y,0 + z);
			point(1 + x,0 + y,0 + z);

			point(1 + x,1 + y,0 + z);
			point(0 + x,1 + y,0 + z);
			point(1 + x,0 + y,0 + z);
		}
	}
}

void BakedChunk::point(GLfloat x, GLfloat y, GLfloat z) {
	mesh.push_back(x);
	mesh.push_back(y);
	mesh.push_back(z);
}

GLfloat* BakedChunk::getMesh() {
	return &mesh[0];
}

int BakedChunk::getSize() {
	return mesh.size() / 3;
}

BakedChunk::~BakedChunk() {
	//dtor
}
