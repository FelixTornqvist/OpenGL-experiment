#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
	public:
		Camera(glm::vec3 pos, float fov, float aspect, float near, float far);

		glm::vec3 getPosition();
		glm::vec3 getRotation();

		glm::mat4 getProjectionMat();
		glm::mat4 getViewMat();

		virtual ~Camera();

	protected:

	private:
		glm::vec3 position, rotation;
		glm::mat4 projection;

		float fov, aspect, near, far;
};

#endif // CAMERA_H
