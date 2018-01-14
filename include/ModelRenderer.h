#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "ModelShader.h"
#include "Model.h"
#include "Camera.h"

class ModelRenderer {
	public:
		ModelRenderer(ModelShader *shader, Camera *cam);

		void render();

		void addModel(Model *model1);

		virtual ~ModelRenderer();

	protected:

	private:
		ModelShader *shader;
		Camera *cam;
		std::vector<Model*> models;
};

#endif // RENDERER_H
