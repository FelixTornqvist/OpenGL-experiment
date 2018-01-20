#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"
#include "Camera.h"
#include "ChunkShader.h"

class World {
	public:
		World(Camera *cam);

		void tick(int millisPassed);
		void render();

		virtual ~World();

	protected:

	private:
		Camera *cam;
		Chunk *tstChunk;
		ChunkShader *chunkShader;
};

#endif // WORLD_H
