// 	g++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test

#include <iostream>
#include <string>
#include <stdlib.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "ModelRenderer.h"
#include "World.h"

std::string programName = "OpenGL test";
SDL_Window *mainWindow;
SDL_GLContext mainContext;

std::vector<Model*> models;
ModelShader *shader;
Camera *camera;
ModelRenderer *mRen;
World* world;

void SetOpenGLAttributes();
void CheckSDLError(int line);

void Render() {
	static Uint32 lastFrame;
	int currFrame = SDL_GetTicks();
//	std::cout << "fps: " << 1000.0 / (currFrame - lastFrame) << std::endl;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mRen->render();
	world->render();

	SDL_GL_SwapWindow(mainWindow);

	lastFrame = currFrame;
}

bool initWindow() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to init SDL\n";
		return false;
	}

	mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								  1024, 1024, SDL_WINDOW_OPENGL);

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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

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
	delete camera;
	delete mRen;
	delete world;

	for (Model* model : models) {
		delete model;
	}

	SDL_GL_DeleteContext(mainContext);
	SDL_DestroyWindow(mainWindow );
	SDL_Quit();
}

void applicationLoop() {
	bool running = true;

	SDL_Event eve;
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	while (running) {

		while (SDL_PollEvent(&eve)) {
			switch (eve.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch (eve.key.keysym.sym ) {
						case SDLK_ESCAPE:
							running = false;
							break;
						case SDLK_m:
							std::cout << "captured:" << SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() == SDL_FALSE? SDL_TRUE : SDL_FALSE) << " off:" << SDL_GetRelativeMouseMode() << std::endl;
					}

					break;
			}
		}

		glm::vec3 dSpeed(0.1);
		glm::vec3 direction = camera->getPointingDirection();
		float camRY = camera->getRotation().y;
		if (state[SDL_SCANCODE_A]) {
			camera->addPostition(glm::vec3(sin(camRY), 0, -cos(camRY)) * dSpeed);
		} else if (state[SDL_SCANCODE_D]) {
			camera->addPostition(glm::vec3(-sin(camRY), 0, cos(camRY)) * dSpeed);
		}

		if (state[SDL_SCANCODE_W]) {
			camera->addPostition(direction * dSpeed);
		} else if (state[SDL_SCANCODE_S]) {
			camera->addPostition(-direction * dSpeed);
		}

		int mDX, mDY;
		SDL_GetRelativeMouseState(&mDX, &mDY);
		camera->addRotation(glm::vec3(.002 * -mDY, .002 * -mDX, 0));
		glm::vec3 camR = camera->getRotation();
		if (camR.x < M_PI_2 + 0.001) {
			camR.x = M_PI_2 + 0.001;
		} else if (camR.x > M_PI + M_PI_2 - 0.001) {
			camR.x = M_PI + M_PI_2 - 0.001;
		}
		camera->setRotation(camR);


		if (state[SDL_SCANCODE_UP]) {
			camera->setFOV(camera->getFOV() + 1);
			std::cout << "FOV: " << camera->getFOV() << std::endl;
		} else if (state[SDL_SCANCODE_DOWN]) {
			camera->setFOV(camera->getFOV() - 1);
			std::cout << "FOV: " << camera->getFOV() << std::endl;
		}

		Render();
	}
}

void addModels(int amount) {
	int dist = 10;
	for (int i = 0; i < amount; i++)
		models.push_back(new Model(glm::vec3(rand() % dist, rand() % dist, rand() % dist) - glm::vec3(dist / 2)));
}

int main(int argc, char *argv[]) {
	if (!initWindow() || !initGL())
		return -1;

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(mainWindow );

	addModels(10);
	shader = new ModelShader();
	shader->UseProgram();
	camera = new Camera(85, 512.0 / 512.0, 0.1, 100);
	mRen = new ModelRenderer(shader, camera);
	world = new World(camera);

	for (Model *model: models) {
		mRen->addModel(model);
	}

	applicationLoop();

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
