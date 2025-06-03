#include "SpesEngineCore/Camera.h"

#include <stdlib.h>

struct Camera* camera_init(struct vec3_float cameraPos, float fov) {
	struct Camera* camera = calloc(1, sizeof(struct Camera));
	if (camera != NULL) {
		camera->fov_ = fov;
		camera->cameraPos_ = cameraPos;
		struct vec3_float vecCamUp = {0.f, 1.f, 0.f};
		camera->cameraUp_ = vecCamUp;
		struct vec3_float vecCamFront = { 0.f, 0.f, -1.f };
		camera->cameraFront_ = vecCamFront;
		struct vec3_float vecCamTarget = { 0.f, 0.f, 0.f };
		camera->cameraTarget_ = vecCamTarget;
		camera->cameraDirection_ = normalize(minus(cameraPos, vecCamTarget));
		struct vec3_float worldUp = { 0.f, 1.f, 0.f };
		camera->worldUp_ = worldUp;
		camera->cameraRight_ = normalize(cross(worldUp, camera->cameraDirection_));
		camera->cameraUp_ = cross(camera->cameraDirection_, camera->cameraRight_);
	}

	return camera;
}

void camera_destroy(struct Camera* camera) {
	free(camera);
	camera = NULL;
}