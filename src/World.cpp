#include <glm/glm.hpp>
#include "World.h"

World::World(Camera *camera): cam(camera) {
	tstChunk = new Chunk();
	tstChunk->setPostition(glm::vec3(10, 0,0));
	chunkShader = new ChunkShader();
}

void World::tick(int millisPassed) {

}

void World::render() {
	glm::mat4 camMat = cam->getProjectionMat() * cam->getViewMat();

	chunkShader->UseProgram();
	tstChunk->bindModel();

	glm::mat4 finalMat = camMat * tstChunk->getTranslationMat();
	chunkShader->setMVPMatrix(finalMat);

	tstChunk->render();
}


World::~World() {
	delete tstChunk;
}
