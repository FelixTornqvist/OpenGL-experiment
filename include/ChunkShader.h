#ifndef CHUNKSHADER_H
#define CHUNKSHADER_H

#include "Shader.h"


class ChunkShader : public Shader {
	public:
		ChunkShader();

		void setMVPMatrix(glm::mat4 mat);

		virtual ~ChunkShader();

	protected:

	private:
		GLint mvpMatrix;
		GLuint vertexshader, fragmentShader;
};

#endif // CHUNKSHADER_H
