#include "SpesEngineCore/Camera.h"

#include <stdlib.h>

#include "Mathemathics/some_func.h"

void camera_init(struct Camera *camera, struct vec3_float cameraPos, float fov)
{
	if (camera != NULL) {
		camera->fov = fov;
		camera->cameraPos = cameraPos;
		struct mat4_float rot = {
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
		camera->cameraRotation = rot;
		updateVectors(camera);
	}
}

void updateVectors(struct Camera* camera)
{
	struct vec4_float f = {0.f, 0.f, -1.f, 1.f};
	struct vec4_float front = mat4_by_vec4(camera->cameraRotation, f);
	struct vec4_float r = { 1.f, 0.f, 0.f, 1.f };
	struct vec4_float right = mat4_by_vec4(camera->cameraRotation, r);
	struct vec4_float u = { 0.f, 1.f, 0.f, 1.f };
	struct vec4_float up = mat4_by_vec4(camera->cameraRotation, u);

	struct vec3_float camFront = {front.x, front.y, front.z};
	struct vec3_float camRight = { right.x, right.y, right.z };
	struct vec3_float camUp = { up.x, up.y, up.z };

	camera->cameraFront = camFront;
	camera->cameraRight = camRight;
	camera->cameraUp = camUp;
}

void camRotate(struct Camera* camera, float x, float y, float z)
{
	struct vec3_float x_ = { 1.f, 0.f, 0.f };
	struct vec3_float y_ = { 0.f, 1.f, 0.f };
	struct vec3_float z_ = { 0.f, 0.f, 1.f };
	camera->cameraRotation = rotate(camera->cameraRotation, x, x_);
	camera->cameraRotation = rotate(camera->cameraRotation, y, y_);
	camera->cameraRotation = rotate(camera->cameraRotation, z, z_);
	updateVectors(camera);
}