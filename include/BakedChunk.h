#ifndef BAKEDCHUNK_H
#define BAKEDCHUNK_H

#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Constants.h"

class BakedChunk {
	public:
		BakedChunk(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]);

		GLfloat* getMesh();
		int getSize();

		virtual ~BakedChunk();

	protected:

	private:
		std::vector<GLfloat> mesh;

		void bake(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]);

		void inline bakeVoxel(
			const int x,
			const int y,
			const int z,
			const bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]
		); 

		/**
		 * Sloping sides are vertical triagles or squares,
		 * but possibly diagonal seen from the top
		 */
		void inline bakeSlopingSide(
			const int x,
			const int y,
			const int z,
			const bool above[4],
			const bool middle[4],
			const bool below[4]
		);

		/**
		 * Regular sides are vertical triangles or squares,
		 * at 90 degree angles seen from the top
		 */
		void inline bakeSide(
			const int x,
			const int y,
			const int z,
			const int above[4],
			const int middle[4]
		);

		/**
		 * Bottoms and tops are triangles or squares,
		 * and may have up to 3 vertices bend down .. I think
		 * if the top have 2 points in opposite corners, they will
		 * form a line.. I think......
		 */
		void inline bakeToppom(
			const int x,
			const int y,
			const int z,
			const bool above[4],
			const bool middle[4],
			const bool below[4],
			const bool bottom
		); 

		/**
		 * Puts a vertex at x,y,z. the cornerIndex goes clockwise
		 * around a square, 1 = top left corner, 3 = bottom right.
		 * Negative cornerIndex puts the vertex one y unit lower.
		 */
		void inline point(GLfloat x, GLfloat y, GLfloat z,
				int cornerIndex);
		void inline point(GLfloat x, GLfloat y, GLfloat z);
};

#endif // BAKEDCHUNK_H
