#include "Mathemathics/vec3_float.h"

#include <math.h>

struct vec3_float cross(struct vec3_float v1, struct vec3_float v2) {
	struct vec3_float res = { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	return res;
}

float dot(struct vec3_float vec1, struct vec3_float vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

struct vec3_float normalize(struct vec3_float vec) {
	float norm = sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);

	struct vec3_float res = {vec.x/norm, vec.y/norm, vec.z/norm};
	return res;
}

struct vec3_float minus(struct vec3_float vec1, struct vec3_float vec2) {
	struct vec3_float res = { vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z };
	return res;
}

struct vec3_float plus(struct vec3_float vec1, struct vec3_float vec2) {
	struct vec3_float res = { vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z };
	return res;
}

struct vec3_float mult_by_numb(struct vec3_float vec, float numb) {
	struct vec3_float res = { vec.x*numb, vec.y*numb, vec.z*numb };
	return res;
}