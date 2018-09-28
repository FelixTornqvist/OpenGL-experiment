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
			int x,
			int y,
			int z,
			bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]
		); 

		void inline point(GLfloat x, GLfloat y, GLfloat z,
				int cornerIndex);
		void inline point(GLfloat x, GLfloat y, GLfloat z);
};

#endif // BAKEDCHUNK_H
