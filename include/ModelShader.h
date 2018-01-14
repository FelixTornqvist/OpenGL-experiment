#ifndef MODELSHADER_H
#define MODELSHADER_H

#include "Shader.h"


class ModelShader : public Shader {
	public:
		ModelShader();

		void setMVPMatrix(glm::mat4 mat);//

		virtual ~ModelShader();

	protected:

	private:
		GLint mvpMatrix;
		GLuint vertexshader, fragmentShader;
};

#endif // MODELSHADER_H
