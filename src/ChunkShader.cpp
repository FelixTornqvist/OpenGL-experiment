#include "ChunkShader.h"
#include "Constants.h"

ChunkShader::ChunkShader() {
	BindAttributeLocation(0, "in_Position");
	BindAttributeLocation(1, "in_Color");

	vertexshader = loadShader(SHADER_DIR + "/tutorial2.vert", GL_VERTEX_SHADER);
	fragmentShader = loadShader(SHADER_DIR + "/tutorial2.frag", GL_FRAGMENT_SHADER);
	linkShaderProgram();

	mvpMatrix = glGetUniformLocation(getProgramID(), "mvp");
}

void ChunkShader::setMVPMatrix(glm::mat4 mat) {
	glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE, &mat[0][0]);
}

ChunkShader::~ChunkShader() {
	glDetachShader(getProgramID(), vertexshader);
	glDetachShader(getProgramID(), fragmentShader);
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentShader);
}
