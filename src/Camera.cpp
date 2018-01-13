#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera(glm::vec3 _pos, float _fov, float _aspect, float _near, float _far):
	position(_pos), fov(_fov), aspect(_aspect), near(_near), far(_far) {
	//ctor
}

glm::vec3 Camera::getPosition() {
	return position;
}

glm::vec3 Camera::getRotation() {
	return rotation;
}

glm::mat4 Camera::getProjectionMat() {
	return glm::perspective(fov, aspect, near, far);
}

glm::mat4 Camera::getViewMat() {
	glm::vec3 camRot(.1, .1, 1);
	return glm::lookAt(position, camRot, glm::vec3(0,-1,0));
}

Camera::~Camera() {
	//dtor
}
