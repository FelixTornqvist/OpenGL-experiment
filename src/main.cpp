// 	g++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test

#include <iostream>
#include <string>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "Shader.h"
#include "Model.h"
#include "ModelRenderer.h"

std::string programName = "OpenGL test";
SDL_Window *mainWindow;
SDL_GLContext mainContext;

Model *model1, *model2;
Shader *shader;
ModelRenderer *mRen;

void SetOpenGLAttributes();
void CheckSDLError(int line);

void Render() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	mRen->render();

	SDL_GL_SwapWindow(mainWindow);
}

bool initWindow() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to init SDL\n";
		return false;
	}

	mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								  512, 512, SDL_WINDOW_OPENGL);

	if (!mainWindow ) {
		std::cout << "Unable to create window\n"<< std::endl;;
		CheckSDLError(__LINE__);
		return false;
	}

	return true;
}

bool initGL() {
	SetOpenGLAttributes();
	mainContext = SDL_GL_CreateContext(mainWindow );

	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	return true;
}

void SetOpenGLAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Cleanup() {
	delete shader;
	delete model1;
	delete model2;

	SDL_GL_DeleteContext(mainContext);
	SDL_DestroyWindow(mainWindow );
	SDL_Quit();
}

int main(int argc, char *argv[]) {
	if (!initWindow() || !initGL())
		return -1;

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(mainWindow );

	model1 = new Model(-.5,0);
	model2 = new Model(.5, 0);
	shader = new Shader();
	shader->UseProgram();
	mRen = new ModelRenderer(shader);

	mRen->addModel(model1);
	mRen->addModel(model2);

	Render();

	std::cout << "Rendering done!\n";
	std::cin.ignore();

	Cleanup();

	return 0;
}

void CheckSDLError(int line = -1) {
	std::string error = SDL_GetError();

	if (error != "") {
		std::cout << "SDL Error : " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}
