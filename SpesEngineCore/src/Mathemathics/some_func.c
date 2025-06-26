#include "Mathemathics/some_func.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Mathemathics/mat4_float.h"
#include "Mathemathics/vec3_float.h"

struct mat4_float LookAt(struct vec3_float eye, struct vec3_float center, struct vec3_float up)
{
	
	struct vec3_float f = normalize(minus(center, eye));
	struct vec3_float s = normalize(cross(f, up));
	struct vec3_float u = cross(s,f);

	struct mat4_float res = {
		s.x, u.x, -f.x, -dot(s, eye),
		s.y, u.y, -f.y, -dot(u, eye),
		s.z, u.z, -f.z, dot(f, eye),
		0, 0, 0, 1
	};
	
	return res;
}

struct mat4_float perspective(float fov, float aspectRatio, float near, float far)
{
	const float FOV_IN_RAD = M_PI * fov / 180.f;

	float tanHalfFOV = tanf(FOV_IN_RAD * 0.5f);

	struct mat4_float perspect = {
		1.f/(aspectRatio*tanHalfFOV), 0.f, 0.f, 0.f,
		0.f, 1.f/(tanHalfFOV), 0, 0,
		0.f, 0.f, (far+near)/(near-far), -1.f,
		0.f, 0.f, 2.f*far*near/(near-far), 0.f
	};
	return perspect;
}

struct mat4_float rotate(struct mat4_float model, float degree, struct vec3_float axis)
{
	float radians = M_PI * degree / 180;

	if (axis.x == 1) {
		struct mat4_float rot_mat = {
			1, 0, 0, 0,
			0, cosf(radians), -sinf(radians), 0,
			0, sinf(radians), cosf(radians), 0,
			0, 0, 0, 1
		};
		return multiply_matrix(rot_mat, model);
	}
	if (axis.y == 1) {
		struct mat4_float rot_mat = {
			cosf(radians), 0, sinf(radians), 0,
			0, 1, 0, 0,
			-sinf(radians), 0, cosf(radians), 0,
			0, 0, 0, 1
		};
		return multiply_matrix(rot_mat, model);
	}
	if (axis.z == 1) {
		struct mat4_float rot_mat = {
			cosf(radians), -sinf(radians), 0, 0,
			sinf(radians), cosf(radians), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		return multiply_matrix(rot_mat, model);
	}
	struct mat4_float res = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
	return res;
}

struct mat4_float translate(struct mat4_float mat, struct vec3_float vec)
{
	struct mat4_float translateMat = {
		1, 0, 0, vec.x,
		0, 1, 0, vec.y,
		0, 0, 1, vec.z,
		0, 0, 0, 1,
	};
	return multiply_matrix(translateMat, mat);
}

struct mat4_float transpose(struct mat4_float mat)
{
	struct mat4_float res = {
		mat.mat[0], mat.mat[4], mat.mat[8], mat.mat[12],
		mat.mat[1], mat.mat[5], mat.mat[9], mat.mat[13],
		mat.mat[2], mat.mat[6], mat.mat[10], mat.mat[14],
		mat.mat[3], mat.mat[7], mat.mat[11], mat.mat[15]
	};
	return res;
}

void* mat4_float_value_ptr(struct mat4_float mat)
{
	return &mat;
}
