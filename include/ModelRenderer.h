#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

class ModelRenderer {
	public:
		ModelRenderer(Shader *shader, Camera *cam);

		void render();

		void addModel(Model *model1);

		virtual ~ModelRenderer();

	protected:

	private:
		Shader *shader;
		Camera *cam;
		std::vector<Model*> models;
};

#endif // RENDERER_H
