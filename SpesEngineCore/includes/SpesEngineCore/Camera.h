#ifndef INCLUDES_SPES_ENGINE_CORE_CAMERA_H
#define INCLUDES_SPES_ENGINE_CORE_CAMERA_H

#include "Mathemathics/mat4_float.h"
#include "Mathemathics/vec3_float.h"

struct Camera {
	struct vec3_float cameraPos, worldUp, cameraRight, cameraUp, cameraFront;
	struct mat4_float cameraRotation;
	float fov;
};

void camera_init(struct Camera* camera, struct vec3_float cameraPos, float fov);

void updateVectors(struct Camera* camera);

void camRotate(struct Camera* camera, float x, float y, float z);

#endif//INCLUDES_SPES_ENGINE_CORE_CAMERA_H