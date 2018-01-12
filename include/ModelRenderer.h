#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "Shader.h"
#include "Model.h"

class ModelRenderer {
	public:
		ModelRenderer(Shader *shader);

		void render();

		void addModel(Model *model1);

		virtual ~ModelRenderer();

	protected:

	private:
		Shader *shader;
		std::vector<Model*> models;
};

#endif // RENDERER_H
