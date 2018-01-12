#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

class Model {
	public:
		Model(float x, float y);

		void loadModel();
		void cleanup();
		void bindModel();

		virtual ~Model();

	protected:

	private:
		GLuint vbo[2], vao[1];

		static const uint32_t points = 4;
		static const uint32_t floatsPerPoint = 3;
		static const uint32_t floatsPerColor = 4;

		GLfloat diamond[points][floatsPerPoint] = {
			{ -0.5,  0.5,  0.5 }, // Top left
			{  0.5,  0.5,  0.5 }, // Top right
			{  0.5, -0.5,  0.5 }, // Bottom right
			{ -0.5, -0.5,  0.5 }, // Bottom left
		};

		GLfloat colors[points][floatsPerColor] = {
			{ 0.0, 1.0, 0.0, 1.0 }, // Top left
			{ 1.0, 1.0, 0.0, 1.0  }, // Top right
			{ 1.0, 0.0, 0.0, 1.0  }, // Bottom right
			{ 0.0, 0.0, 1.0, 1.0  }, // Bottom left
		};

		// The positons of the position and color data within the VAO
		const uint32_t positionAttributeIndex = 0, colorAttributeIndex = 1;
};

#endif // MODEL_H
