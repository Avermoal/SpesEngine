#ifndef INCLUDES_MATHEMATHICS_MAT4_FLOAT_H
#define INCLUDES_MATHEMATHICS_MAT4_FLOAT_H

struct mat4_float {
	float mat[16];
};

struct vec4_float {
	float x, y, z, w;
};

struct mat4_float multiply_matrix(struct mat4_float m1, struct mat4_float m2);

struct vec4_float mat4_by_vec4(struct mat4_float m, struct vec4_float v);

#endif//INCLUDES_MATHEMATHICS_MAT4_FLOAT_H