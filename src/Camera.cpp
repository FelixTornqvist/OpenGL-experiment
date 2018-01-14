#include <iostream>
#include <math.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera(float _fov, float _aspect, float _near, float _far):
	position(0), rotation(0, 0, 1), fov(_fov), aspect(_aspect), near(_near), far(_far) {
	//ctor
}

glm::mat4 Camera::getProjectionMat() {
	return glm::perspective(fov, aspect, near, far);
}

glm::mat4 Camera::getViewMat() {
	return glm::lookAt(position, getPointingDirection() + position, glm::vec3(0,-1,0));
}

glm::vec3 Camera::getPointingDirection() {
	float pitch = rotation.x;
	float yaw = rotation.y;

	glm::vec3 direction;
	direction.x = cos(pitch) * cos(yaw);
	direction.y = sin(pitch);
	direction.z = cos(pitch) * sin(yaw);
	return direction;
}

void Camera::setPostition(glm::vec3 pos) {
	position = pos;
}

void Camera::setRotation(glm::vec3 rot) {
	rotation = rot;
}


void Camera::addPostition(glm::vec3 pos) {
	position += pos;
}

void Camera::addRotation(glm::vec3 rot) {
	rotation += rot;
	glm::vec3 pie(M_PI * 2);
	rotation = glm::mod(rotation, pie);
}


glm::vec3 Camera::getPostition() {
	return position;
}

glm::vec3 Camera::getRotation() {
	return rotation;
}


Camera::~Camera() {
	//dtor
}
