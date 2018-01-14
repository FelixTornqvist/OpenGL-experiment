#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
	public:
		Camera(float fov, float aspect, float near, float far);

		glm::mat4 getProjectionMat();
		glm::mat4 getViewMat();
		glm::vec3 getPointingDirection();

		void setPostition(glm::vec3 pos);
		void setRotation(glm::vec3 rot);

		void addPostition(glm::vec3 pos);
		void addRotation(glm::vec3 rot);

		glm::vec3 getPostition();
		glm::vec3 getRotation();

		virtual ~Camera();

	protected:

	private:
		glm::vec3 position, rotation;
		glm::mat4 projection;

		float fov, aspect, near, far;
};

#endif // CAMERA_H
