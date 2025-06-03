#include "SpesEngineCore/Camera.h"

void Camera::init_camera(float fov) {
	
}

glm::mat4 Camera::rotation(float x, float y, float z) {
	return glm::mat4(1.0f);
}

glm::mat4 Camera::getProjection() {
	return glm::mat4(1.0f);
}

glm::mat4 Camera::getView() {
	return glm::mat4(1.0f);
}

void Camera::updateVectors() {

}