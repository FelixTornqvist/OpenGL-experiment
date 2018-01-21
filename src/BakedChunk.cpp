#include "BakedChunk.h"

BakedChunk::BakedChunk(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
	bake(points);
}

void BakedChunk::bake(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
//	mesh.push_back(point(10,10,10));
//	mesh.push_back(point(10,11,10));
//	mesh.push_back(point(11,10,10));
//
//	mesh.push_back(point(10,10,11));
//	mesh.push_back(point(10,11,10));
//	mesh.push_back(point(11,10,10));

	for (int i = 0; i < 50; i += 2) {
		mesh.push_back(point(0 + i,0 + i,0 + i));
		mesh.push_back(point(0 + i,1 + i,0 + i));
		mesh.push_back(point(1 + i,0 + i,0 + i));

		mesh.push_back(point(0 + i,0 + i,1 + i));
		mesh.push_back(point(0 + i,1 + i,0 + i));
		mesh.push_back(point(1 + i,0 + i,0 + i));
	}
//	mesh.push_back(point(0,0,0));
//	mesh.push_back(point(0,1,0));
//	mesh.push_back(point(1,0,0));
//
//	mesh.push_back(point(0,0,1));
//	mesh.push_back(point(0,1,0));
//	mesh.push_back(point(1,0,0));
}

uint BakedChunk::point(uint x, uint y, uint z) {
	uint mask = 0x3FF; // binary: 0b00000000000000000000001111111111
	x &= mask;
	y &= mask;
	z &= mask;
	return x | y << 10 | z << 20;
}

uint* BakedChunk::getMesh() {
	return &mesh[0];
}

int BakedChunk::getSize() {
	return mesh.size();
}

BakedChunk::~BakedChunk() {
	//dtor
}
