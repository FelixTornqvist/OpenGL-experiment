#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

#include "Shader.h"


Shader::Shader() {
	shaderProgram = glCreateProgram();

	BindAttributeLocation(0, "in_Position");
	BindAttributeLocation(1, "in_Color");

	vertexshader = loadShader("tutorial2.vert", GL_VERTEX_SHADER);
	fragmentShader = loadShader("tutorial2.frag", GL_FRAGMENT_SHADER);

	linkShaderProgram();

	mvpMatrix = glGetUniformLocation(shaderProgram, "mvp");
}

std::string Shader::ReadFile(const char* file) {
	std::ifstream t(file);
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string fileContent = buffer.str();

	return fileContent;
}

void Shader::BindAttributeLocation(int index, const std::string &attribute) {
	glBindAttribLocation(shaderProgram, index, attribute.c_str());
}


void Shader::setMVPMatrix(glm::mat4 mat) {
	glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE, &mat[0][0]);
}

void Shader::UseProgram() {
	glUseProgram(shaderProgram);
}

GLuint Shader::loadShader(const std::string &filename, GLenum shaderType) {
	GLuint shader;
	std::string str = ReadFile(filename.c_str());

	char* src = const_cast<char*>( str.c_str());
	int32_t size = str.length();

	shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &src, &size);
	glCompileShader(shader);

	int wasCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &wasCompiled );

	if (wasCompiled == 0) {
		throw std::runtime_error("error while compiling shader: " + getShaderCompilationErrorInfo(shader));
	}

	glAttachShader(shaderProgram, shader);
	return shader;
}

void Shader::linkShaderProgram() {
	glLinkProgram(shaderProgram);

	int isLinked;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == false)
		throw std::runtime_error("error while linking shader: " + getShaderLinkingError(shaderProgram));
}

std::string Shader::getShaderLinkingError(int32_t shaderId) {
	int maxLength;
	glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

	char* shaderProgramInfoLog = new char[maxLength];
	glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, shaderProgramInfoLog);

	std::string log(shaderProgramInfoLog);

	delete shaderProgramInfoLog;

	return log;
}

std::string Shader::getShaderCompilationErrorInfo(int32_t shaderId) {
	int maxLength;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

	char* shaderInfoLog = new char[maxLength];
	glGetShaderInfoLog(shaderId, maxLength, &maxLength, shaderInfoLog );

	std::string log(shaderInfoLog);

	delete shaderInfoLog;

	return log;
}

Shader::~Shader() {
	glUseProgram(0);
	glDetachShader(shaderProgram, vertexshader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteProgram(shaderProgram);

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentShader);
}


