#include "Camera.hpp"

namespace gps {

	//Camera constructor
	Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUpDirection) {
		//TODO

		this->cameraPosition = cameraPosition;
		this->cameraTarget = cameraTarget;
		this->cameraFrontDirection = glm::normalize(cameraPosition - cameraTarget); //cameraDirection
		this->cameraRightDirection = glm::normalize(glm::cross(cameraUpDirection, cameraFrontDirection));
		this->cameraUpDirection = glm::cross(cameraFrontDirection, cameraRightDirection);

	}

	//return the view matrix, using the glm::lookAt() function
	glm::mat4 Camera::getViewMatrix() {
		//TODO

	   //return glm::mat4();
		return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f));

	}

	//update the camera internal parameters following a camera move event
	void Camera::move(MOVE_DIRECTION direction, float speed) {
		//TODO
		switch (direction) {
		case MOVE_LEFT:
			cameraPosition = cameraPosition - cameraRightDirection * speed;
			break;

		case MOVE_RIGHT:
			cameraPosition = cameraPosition + cameraRightDirection * speed;
			break;

		case MOVE_BACKWARD:
			cameraPosition = cameraPosition - cameraFrontDirection * speed;
			break;

		case MOVE_FORWARD:
			cameraPosition = cameraPosition + cameraFrontDirection * speed;
			break;
		}
		
	}

		void Camera::rotate(float pitch, float yaw) {
		//TODO
		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

		cameraFrontDirection = glm::normalize(front);
	}

	void Camera::scenePreview(float angle) {
		// set the camera
		this->cameraPosition = glm::vec3(-9.0, 20.0, 48.0);

		// rotate with specific angle around Y axis
		glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));

		this->cameraPosition = glm::vec4(r * glm::vec4(this->cameraPosition, 1));
		this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
		cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
	}
}