#ifndef INCLUDES_MATHEMATHICS_VEC3_FLOAT_H
#define INCLUDES_MATHEMATHICS_VEC3_FLOAT_H

struct vec3_float {
	float x, y, z;
};

struct vec3_float cross(struct vec3_float v1, struct vec3_float v2);

float dot(struct vec3_float vec1, struct vec3_float vec2);

struct vec3_float normalize(struct vec3_float vec);

struct vec3_float minus(struct vec3_float vec1, struct vec3_float vec2);

struct vec3_float plus(struct vec3_float vec1, struct vec3_float vec2);

struct vec3_float mult_by_numb(struct vec3_float vec, float numb);

#endif//INCLUDES_MATHEMATHICS_VEC3_FLOAT_H