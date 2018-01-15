#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Model {
	public:
		Model(glm::vec3 pos);

		void bindModel();

		glm::mat4 getTranslationMat();

		void setPostition(glm::vec3 pos);
		void setRotation(glm::vec3 rot);
		void setScale(glm::vec3 scale);

		void addPostition(glm::vec3 pos);
		void addRotation(glm::vec3 rot);
		void addScale(glm::vec3 scale);

		glm::vec3 getPostition();
		glm::vec3 getRotation();
		glm::vec3 getScale();

		virtual ~Model();

	protected:

	private:
		glm::vec3 position, rotation, scale;
		GLuint vbo[2], vao[1];
		// The positons of the position and color data within the VAO
		const uint32_t positionAttributeIndex = 0, colorAttributeIndex = 1;

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

		void loadModel();
};

#endif // MODEL_H
