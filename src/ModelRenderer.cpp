#include "ModelRenderer.h"

ModelRenderer::ModelRenderer(Shader *s): shader(s) {
}

void ModelRenderer::render() {
	for (Model* model : models) {
		model->bindModel();
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
}

void ModelRenderer::addModel(Model* model1) {
	models.push_back(model1);
}

ModelRenderer::~ModelRenderer() {
}
