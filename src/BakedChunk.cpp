#include <iostream>
#include "BakedChunk.h"

BakedChunk::BakedChunk(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
	bake(points);
}

void BakedChunk::bake(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {

	for (int x = 0; x < CHUNK_SIZE - 1; x++) {
		for (int y = 0; y < CHUNK_SIZE - 1; y++) {
			for (int z = 0; z < CHUNK_SIZE - 1; z++) {
				bakeVoxel(x, y, z, points);
			}
		}
	}
}

/**
 Corner indexes of voxel
 0 = 0,0,0
 4 = 0,1,0
 1 = 1,0,0
 3 = 0,0,1
 6 = 1,1,1 etc.
  Top:
 0--------1
 |        |
 |        |
 |        |
 3--------2

  Bottom:
 4--------5
 |        |
 |        |
 |        |
 7--------6
*/
void BakedChunk::bakeVoxel(int x, int y, int z, bool(& p)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
	bool c[8];

	c[0] = p[x][y][z];
	c[1] = p[x+1][y][z];
	c[2] = p[x+1][y][z+1];
	c[3] = p[x][y][z+1];

	c[4] = p[x][y+1][z];
	c[5] = p[x+1][y+1][z];
	c[6] = p[x+1][y+1][z+1];
	c[7] = p[x][y+1][z+1];

	if (!(c[0] || c[1] || c[2] || c[3] || c[4] || c[5] || c[6] || c[7]))
		return;

	// Make top face
	// crease along what direction?
	int vStart = 0;						// 0 = crease from 0 to 2, 1 = crease from 1 to 3
	if ( (c[0] && c[2]) ) {
		vStart = 0;
	} else if ( (c[1] && c[3])) {
		vStart = 1;
	} else if ( c[4] && c[6]) {
		vStart = 0;
	} else if ( c[5] && c[7]) {
		vStart = 1;
	}

	int tri[3];
	for (int start = vStart; start < 3 + vStart; start += 2) {

		for (int v = 0; v < 3; v++) {

			if (c[(v + start) % 4]) {
				tri[v] = (v + start) % 4;
			} else if (c[((v + start) % 4) + 4]) {
				tri[v] = ((v + start) % 4) + 4;
			} else {
				tri[0] = -1;
				break;
			}

		}
		if (tri[0] != -1) {
			for (int corn : tri) {
				point(x,y,z, corn);
			}
		}

	}

	// Top face done, make sides
	for (int i = 0; i < 4; i++) {
		int i1 = (i + 1) % 4;
		int top = 0;

		if (c[i1]) {
			tri[top++] = i1;
		}
		if (c[i]) {
			tri[top++] = i;
		}
		if (c[i+4]) {
			tri[top++] = i + 4;
		}
		if (c[i1+4]) {
			if (top != 3) {
				tri[top++] = i1 + 4;
			} else {
				point(x,y,z, i + 4);
				point(x,y,z, i1 + 4);
				point(x,y,z, i1);
			}
		}
		if (top > 2)
			for (int corn : tri) {
				point(x,y,z, corn);
			}
	}
}

void BakedChunk::point(GLfloat x, GLfloat y, GLfloat z, int cornerIndex) {
	switch (cornerIndex) {
		case 0:
			point(x, y, z);
			break;
		case 1:
			point(x+1, y, z);
			break;
		case 2:
			point(x+1, y, z+1);
			break;
		case 3:
			point(x, y, z+1);
			break;
		case 4:
			point(x, y+1, z);
			break;
		case 5:
			point(x+1, y+1, z);
			break;
		case 6:
			point(x+1, y+1, z+1);
			break;
		case 7:
			point(x, y+1, z+1);
			break;
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
