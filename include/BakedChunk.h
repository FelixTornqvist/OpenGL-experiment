#ifndef BAKEDCHUNK_H
#define BAKEDCHUNK_H

#include <vector>

#include <glm/glm.hpp>

#include "Constants.h"

class BakedChunk {
	public:
		BakedChunk(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]);

		uint* getMesh();
		int getSize();

		virtual ~BakedChunk();

	protected:

	private:
		std::vector<uint> mesh;

		void bake(bool (&points)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]);
		uint point(uint x, uint y, uint z);
};

#endif // BAKEDCHUNK_H
