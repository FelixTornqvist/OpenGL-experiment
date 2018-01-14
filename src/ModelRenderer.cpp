#include "ModelRenderer.h"

ModelRenderer::ModelRenderer(ModelShader *s, Camera *_cam): shader(s), cam(_cam) {
}

void ModelRenderer::render() {
	glm::mat4 camMat = cam->getProjectionMat() * cam->getViewMat();

	for (Model* model : models) {
		model->bindModel();

		glm::mat4 finalMat = camMat * model->getTranslationMat();
		shader->setMVPMatrix(finalMat);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
}

void ModelRenderer::addModel(Model* model1) {
	models.push_back(model1);
}

ModelRenderer::~ModelRenderer() {
}
