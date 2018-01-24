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
	if (p[x][y][z]) {
		bool c[8];

		c[0] = p[x][y][z];
		c[1] = p[x+1][y][z];
		c[2] = p[x+1][y][z+1];
		c[3] = p[x][y][z+1];

		c[4] = p[x][y+1][z];
		c[5] = p[x+1][y+1][z];
		c[6] = p[x+1][y+1][z+1];
		c[7] = p[x][y+1][z+1];

		std::cout << "baking: ";
		for (bool tu : c)
			std::cout << tu;
		std::cout << std::endl;

		// Make top face
		// crease along what direction?
		if ( (c[0] || c[2]) && (!c[1] || !c[3]) ) {			//crease from 0 to 2
			std::cout << "0-2"<< std::endl;

			int tri1[3];
			for (int start = 0; start < 3; start += 2) {
				std::cout << "start: "<< start<< std::endl;

				for (int i = 0; i < 3; i++) {

					if (c[(i + start) % 4])
						tri1[i] = (i + start) % 4;
					else if (c[((i + start) % 4) + 4])
						tri1[i] = ((i + start) % 4) + 4;
					else {
						tri1[0] = -1;
//						break;
					}
					std::cout << "tri1[" << i << "]: "<< tri1[i] << std::endl;

				}
				if (tri1[0] != -1) {
					std::cout << "--------------not -1!------------"<< std::endl;
					for (int corn : tri1) {
						std::cout << "made: " << corn << std::endl;
						point(x,y,z, corn);
					}
				}

			}


		} else if((c[1] || c[3]) && (!c[0] || !c[2])) {		//crease from 1 to 3
			std::cout << "1-3"<< std::endl;
		}

//		for (int i = 0; i < 4; i++) {
//			if (c[i]) {
//				point(x,y,z, i);
//			} else if (c[i+4]){
//				point(x,y,z, i + 4);
//			}
//		}
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
