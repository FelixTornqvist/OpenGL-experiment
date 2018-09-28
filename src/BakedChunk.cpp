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
  Top:
 1--------2
 |        |
 |        |
 |        |
 4--------3

  Bottom (numbers are negative):
 1--------2
 |        |
 |        |
 |        |
 4--------3

 top 1 = 0,0,0
 bottom 3 = 1,-1,1

 Conversion table: (T = top, B = Bottom)
 T1 0,0,0
 T2 1,0,0
 T3 1,0,1
 T4 0,0,1

 B1 0,-1,0
 B2 1,-1,0
 B3 1,-1,1
 B4 0,-1,1
*/
void BakedChunk::bakeVoxel(const int x, const int y, const int z, 
		const bool(& p)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {

	auto n = [p,x,y,z](int lvl[4], int lvlIndex, int corner, int xa, int ya, int za) 
		-> void {
		lvl[lvlIndex] = p[x+xa][y+ya][z+za]? corner : 0;
	};

	int above[4];
	int middle[4];
	int below[4];

	// Setup for top
	n(above, 0, true, 0, 1, 0);
	n(above, 1, true, 1, 1, 0);
	n(above, 2, true, 1, 1, 1);
	n(above, 3, true, 0, 1, 1);
	
	n(middle, 0, 1, 0, 0, 0);
	n(middle, 1, 2, 1, 0, 0);
	n(middle, 2, 3, 1, 0, 1);
	n(middle, 3, 4, 0, 0, 1);

	n(below, 0, -1, 0, -1, 0);
	n(below, 1, -2, 1, -1, 0);
	n(below, 2, -3, 1, -1, 1);
	n(below, 3, -4, 0, -1, 1);	

//	bakeToppom(x, y, z, above, middle, below, false);

	if (!(above[0] && above[1] && above[2] && above[3]))
		bakeSide(x, y, z, above, middle);

	// Setup for back
	n(above, 0, true, 1, 0, -1);
	n(above, 1, true, 0, 0, -1);
	n(above, 2, true, 0, -1, -1);
	n(above, 3, true, 1, -1, -1);
	
	n(middle, 0, 2, 1, 0, 0);
	n(middle, 1, 1, 0, 0, 0);
	n(middle, 2, -1, 0, -1, 0);
	n(middle, 3, -2, 1, -1, 0);

	n(below, 0, 3, 1, 0, 1);
	n(below, 1, 4, 0, 0, 1);
	n(below, 2, -4, 0, -1, 1);
	n(below, 3, -3, 1, -1, 1);

	if (!(above[0] && above[1] && above[2] && above[3]))
		bakeSide(x, y, z, above, middle);

	// Setup for right
	n(above, 0, true, 2, 0, 1);
	n(above, 1, true, 2, 0, 0);
	n(above, 2, true, 2, -1, 0);
	n(above, 3, true, 2, -1, 1);
	
	n(middle, 0, 3, 1, 0, 1);
	n(middle, 1, 2, 1, 0, 0);
	n(middle, 2, -2, 1, -1, 0);
	n(middle, 3, -3, 1, -1, 1);

	n(below, 0, 4, 0, 0, 1);
	n(below, 1, 1, 0, 0, 0);
	n(below, 2, -1, 0, -1, 0);
	n(below, 3, -4, 0, -1, 1);

	if (!(above[0] && above[1] && above[2] && above[3]))
		bakeSide(x, y, z, above, middle);

	// Setup for front
	n(above, 0, true, 0, 0, 2);
	n(above, 1, true, 1, 0, 2);
	n(above, 2, true, 1, -1, 2);
	n(above, 3, true, 0, -1, 2);

	n(middle, 0, 4, 0, 0, 1);
	n(middle, 1, 3, 1, 0, 1);
	n(middle, 2, -3, 1, -1, 1);
	n(middle, 3, -4, 0, -1, 1);

	n(below, 0, 1, 0, 0, 0);
	n(below, 1, 2, 1, 0, 0);
	n(below, 2, -2, 1, -1, 0);
	n(below, 3, -1, 0, -1, 0);

	if (!(above[0] && above[1] && above[2] && above[3]))
		bakeSide(x, y, z, above, middle);

	// Setup for left
	n(above, 0, true, -1, 0, 0);
	n(above, 1, true, -1, 0, 1);
	n(above, 2, true, -1, -1, 1);
	n(above, 3, true, -1, -1, 0);

	n(middle, 0, 1, 0, 0, 0);
	n(middle, 1, 4, 0, 0, 1);
	n(middle, 2, -4, 0, -1, 1);
	n(middle, 3, -1, 0, -1, 0);

	n(below, 0, 2, 1, 0, 0);
	n(below, 1, 3, 1, 0, 1);
	n(below, 2, -3, 1, -1, 1);
	n(below, 3, -2, 1, -1, 0);

	if (!(above[0] && above[1] && above[2] && above[3]))
		bakeSide(x, y, z, above, middle);

	//TEMPORARY BEGIN---
	auto m = [p,x,y,z](int xa, int ya, int za) -> bool {
		return p[x+xa][y+ya][z+za];
	};
	auto triang = [this](int x, int y, int z, bool up) -> void {
		const float s = 0.1f;
		if (up) {
			point(x,y,z);
			point(x-s, y+s, z);
			point(x+s, y+s, z);
		} else {
			point(x,y,z);
			point(x-s, y-s, z);
			point(x+s, y-s, z);
		}
	};

	if (m(0, -1, 0))
		triang(x+0, y-1, z+0, false);
	if (m(1, -1, 0))
		triang(x+1, y-1, z+0, false);
	if (m(1, -1, 1))
		triang(x+1, y-1, z+1, false);
	if (m(0, -1, 1))
		triang(x+0, y-1, z+1, false);

	if (m(0, 0, 0))
		triang(x+0, y, z+0, true);
	if (m(1, 0, 0))
		triang(x+1, y, z+0, true);
	if (m(1, 0, 1))
		triang(x+1, y, z+1, true);
	if (m(0, 0, 1))
		triang(x+0, y, z+1, true);
	// TEMPORARY END---

	/*

	// Top face done, make bottom face
	if ( c[4] && c[6] ) {
		vStart = 0; // 0 = crease from 0 to 2, 1 = crease from 1 to 3
	} else if ( c[5] && c[7] ) {
		vStart = 1;
	} else if ( c[0] && c[2] ) {
		vStart = 0;
	} else if ( c[1] && c[3] ) {
		vStart = 1;
	}

	for (int start = vStart; start < 3 + vStart; start += 2) {

		for (int v = 0; v < 3; v++) {

			if (c[((v + start) % 4) + 4]) {
				tri[v] = ((v + start) % 4) + 4;
			} else if (c[(v + start) % 4]) {
				tri[v] = (v + start) % 4;
			} else {
				tri[0] = -1;
				break;
			}

		}
		if (tri[0] != -1) {
			for (int i = 2; i > -1; i--) {
				point(x,y,z, tri[i]);
			}
		}

	}

	// Bottom face done, make left and right sides
	for (int i = 1; i < 4; i+=2) {
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

	// make back side.
	// flat
	if (c[4] && c[1]) {
		if (c[0]) {
			point(x,y,z,0);
			point(x,y,z,4);
			point(x,y,z,1);
		}
		if (c[5]) {
			point(x,y,z,4);
			point(x,y,z,5);
			point(x,y,z,1);
		}

	} else if (c[0] && c[5]) {
		if (c[4]) {
			point(x,y,z,0);
			point(x,y,z,4);
			point(x,y,z,5);
		}
		if (c[1]) {
			point(x,y,z,0);
			point(x,y,z,5);
			point(x,y,z,1);
		}
	}
	//left bent in
//	else if ( (c[3] || c[7]) && (c[1] || c[5])) {
	else if (c[1] && c[7] && !c[4]) {
		if (c[3] && !c[0]) {
			point(x,y,z,1);
			point(x,y,z,3);
			point(x,y,z,7);
		}
		if (c[5]) {
			point(x,y,z,1);
			point(x,y,z,7);
			point(x,y,z,5);
		}

	} else if (c[3] && c[5] && !c[0]) {
		if (c[1]) {
			point(x,y,z,3);
			point(x,y,z,5);
			point(x,y,z,1);
		}
		if (c[7] && !c[4]) {
			point(x,y,z,3);
			point(x,y,z,7);
			point(x,y,z,5);
		}
	}
	//right bent in
	else if (c[2] && c[4] && !c[1]) {
		if (c[0]) {
			point(x,y,z,2);
			point(x,y,z,0);
			point(x,y,z,4);
		}
		if (c[6] && !c[5]) {
			point(x,y,z,2);
			point(x,y,z,4);
			point(x,y,z,6);
		}

	} else if (c[0] && c[6] && !c[5]) {
		if (c[2] && !c[1]) {
			point(x,y,z,0);
			point(x,y,z,6);
			point(x,y,z,2);
		}
		if (c[4]) {
			point(x,y,z,0);
			point(x,y,z,4);
			point(x,y,z,6);
		}
	}*/
}

void BakedChunk::bakeToppom(const int x, const int y, const int z, 
		const bool above[4], const bool middle[4], const bool below[4],
		const bool bottom) {
	// crease along what direction?
	int vStart = 0;	// 0 = crease from 0 to 2, 1 = crease from 1 to 3
	if ( middle[0] && middle[2] ) {
		vStart = 0;
	} else if ( middle[1] && middle[3] ) {
		vStart = 1;
	} else if ( below[0] && below[2] ) {
		vStart = 0;
	} else if ( below[1] && below[3] ) {
		vStart = 1;
	} else {
		return;
	}

	int tri[3];
	// create 2 triangles with different start positions
	// if vStart = 0, crease from 0 to 2, if = 1, crease from 1 to 3
	for (int start = vStart; start < 3 + vStart; start += 2) {

		// Create 3 vertices (a triangle) firstly trying middle
		// and then below
		for (int v = 0; v < 3; v++) {
			int corner = (v + start) % 4 + 1;

			if (middle[corner]) {
				tri[v] = corner;

			} else if (below[corner]) {
				tri[v] = -corner;

			} else { // Failed to create a full triangle
				tri[0] = 0;
				break;
			}

		}
		if (tri[0] != 0) {
			for (int corn : tri) {
				point(x,y,z, corn);
			}
		}

	}
}

void BakedChunk::bakeSide(const int x, const int y, const int z,
		const int above[4], const int middle[4]) {
	if (middle[0] && middle[2]) {
		if (middle[1]) {
			point(x,y,z,middle[0]);
			point(x,y,z,middle[1]);
			point(x,y,z,middle[2]);
		} 
		if (middle[3]) {
			point(x,y,z,middle[0]);
			point(x,y,z,middle[2]);
			point(x,y,z,middle[3]);
		}
	} else if (middle[1] && middle[3]) {
		if (middle[2]) {
			point(x,y,z,middle[1]);
			point(x,y,z,middle[2]);
			point(x,y,z,middle[3]);
		} 
		if (middle[0]) {
			point(x,y,z,middle[1]);
			point(x,y,z,middle[3]);
			point(x,y,z,middle[0]);
		}
	}
}


void BakedChunk::point(GLfloat x, GLfloat y, GLfloat z, int cornerIndex) {
	switch (cornerIndex) {
		case 1:
			point(x, y, z);
			break;
		case 2:
			point(x+1, y, z);
			break;
		case 3:
			point(x+1, y, z+1);
			break;
		case 4:
			point(x, y, z+1);
			break;
		case -1:
		        point(x, y-1, z);
		        break;
		case -2:
		        point(x+1, y-1, z);
		        break;
		case -3:
		        point(x+1, y-1, z+1);
		        break;
		case -4:
			point(x, y-1, z+1);
			break;
		default:
			std::cerr << "programming error " << __FILE__ << ':' 
				<< __LINE__ << std::endl;
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
