#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Constants.h"
#include "BakedChunk.h"

class Chunk {
	public:
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
		bool points[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE] = {{{false}}};
		GLuint vbo[2], vao[1];
		// The positons of the position and color data within the VAO
		const uint32_t positionAttributeIndex = 0;
		const uint32_t colorAttributeIndex = 1;

		int floatsPerColor = 4;
		int vbSize;

		void fillTerrainPoints();
		void loadModel(GLfloat *arr, int siz);
		void genRandFloats(GLfloat* arrLoc, int amount);
};

#endif // CHUNK_H
