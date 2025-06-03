#ifndef INCLUDES_MATHEMATHICS_MAT4_FLOAT_H
#define INCLUDES_MATHEMATHICS_MAT4_FLOAT_H

struct mat4_float {
	float mat[16];
};
struct mat4_float multiply_matrix(struct mat4_float m1, struct mat4_float m2);

#endif//INCLUDES_MATHEMATHICS_MAT4_FLOAT_H