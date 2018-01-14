#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <string>

class Shader {
	public:
		void BindAttributeLocation(int index, const std::string &attribute);

		void UseProgram();

		~Shader();

	protected:
		Shader();
		GLuint getProgramID();

		/** Throws runtime_exception if there was an error loading the shader*/
		GLuint loadShader(const std::string &filename, GLenum shaderType);
		/** Throws runtime_exception if there was an error linking the shader program*/
		void linkShaderProgram();

	private:
		GLuint shaderProgram;

		std::string ReadFile(const char* file);

		std::string getShaderLinkingError(int32_t shaderId);
		std::string getShaderCompilationErrorInfo(int32_t shaderId);

};
