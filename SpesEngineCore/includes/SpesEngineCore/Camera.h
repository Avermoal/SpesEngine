#ifndef INCLUDES_SPES_ENGINE_CORE_CAMERA_H
#define INCLUDES_SPES_ENGINE_CORE_CAMERA_H

#include "Mathemathics/vec3_float.h"

struct Camera {
	struct vec3_float cameraPos_, cameraTarget_, cameraDirection_, worldUp_, cameraRight_, cameraUp_, cameraFront_;
	float fov_;
};

struct Camera* camera_init(struct vec3_float cameraPos, float fov);

void camera_destroy(struct Camera* camera);

#endif//INCLUDES_SPES_ENGINE_CORE_CAMERA_H