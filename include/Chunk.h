#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "BakedChunk.h"

class Chunk {
	public:
		static const int SIZE = 10;

		Chunk();

		void bindModel();
		void render();

		glm::mat4 getTranslationMat();

		void setPostition(glm::vec3 pos);
		glm::vec3 getPostition();

		virtual ~Chunk();

	protected:

	private:
		glm::vec3 position;
		bool points[SIZE][SIZE][SIZE];
		GLuint vbo[2], vao[1];
		// The positons of the position and color data within the VAO
		const uint32_t positionAttributeIndex = 0, colorAttributeIndex = 1;
		int floatsPerColor = 4;
		int vbSize;

		void fillTerrainPoints();
		void loadModel(uint *arr, int siz);
		void genRandFloats(GLfloat* arrLoc, int amount);
};

#endif // CHUNK_H
