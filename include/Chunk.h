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

		glm::mat4 getTranslationMat();

		void setPostition(glm::vec3 pos);
		glm::vec3 getPostition();

		virtual ~Chunk();

	protected:

	private:
		glm::vec3 position;
		bool points[SIZE][SIZE][SIZE];
		GLuint vbo[1], vao[1];
		// The positons of the position and color data within the VAO
		const uint32_t positionAttributeIndex = 0;

		void fillTerrainPoints();
		void loadModel(uint *arr, int siz);
};

#endif // CHUNK_H
