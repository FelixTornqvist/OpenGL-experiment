#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"

class World {
	public:
		World();

		void tick(int millisPassed);
		void render();

		virtual ~World();

	protected:

	private:
		Chunk *tstChunk;
};

#endif // WORLD_H
