#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <string>

class Shader {
	public:
		Shader();

		void BindAttributeLocation(int index, const std::string &attribute);

		void UseProgram();

		~Shader();

	private:
		GLuint shaderProgram;
		GLuint vertexshader, fragmentShader;

		std::string ReadFile(const char* file);

		/** Throws runtime_exception if there was an error loading the shader*/
		GLuint loadShader(const std::string &filename, GLenum shaderType);
		/** Throws runtime_exception if there was an error linking the shader program*/
		void linkShaderProgram();

		std::string getShaderLinkingError(int32_t shaderId);
		std::string getShaderCompilationErrorInfo(int32_t shaderId);

};