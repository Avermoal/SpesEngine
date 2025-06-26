#include "Mathemathics/mat4_float.h"

struct mat4_float multiply_matrix(struct mat4_float m1, struct mat4_float m2) {
	struct mat4_float res = {
	m1.mat[0] * m2.mat[0] + m1.mat[1] * m2.mat[4] + m1.mat[2] * m2.mat[8] + m1.mat[3] * m2.mat[12], m1.mat[0] * m2.mat[1] + m1.mat[1] * m2.mat[5] + m1.mat[2] * m2.mat[9] + m1.mat[3] * m2.mat[13], m1.mat[0] * m2.mat[2] + m1.mat[1] * m2.mat[6] + m1.mat[2] * m2.mat[10] + m1.mat[3] * m2.mat[14], m1.mat[0] * m2.mat[3] + m1.mat[1] * m2.mat[7] + m1.mat[2] * m2.mat[11] + m1.mat[3] * m2.mat[15],
	m1.mat[4] * m2.mat[0] + m1.mat[5] * m2.mat[4] + m1.mat[6] * m2.mat[8] + m1.mat[7] * m2.mat[12], m1.mat[4] * m2.mat[1] + m1.mat[5] * m2.mat[5] + m1.mat[6] * m2.mat[9] + m1.mat[7] * m2.mat[13], m1.mat[4] * m2.mat[2] + m1.mat[5] * m2.mat[6] + m1.mat[6] * m2.mat[10] + m1.mat[7] * m2.mat[14], m1.mat[4] * m2.mat[3] + m1.mat[5] * m2.mat[7] + m1.mat[6] * m2.mat[11] + m1.mat[7] * m2.mat[15],
	m1.mat[8] * m2.mat[0] + m1.mat[9] * m2.mat[4] + m1.mat[10] * m2.mat[8] + m1.mat[11] * m2.mat[12], m1.mat[8] * m2.mat[1] + m1.mat[9] * m2.mat[5] + m1.mat[10] * m2.mat[9] + m1.mat[11] * m2.mat[13], m1.mat[8] * m2.mat[2] + m1.mat[9] * m2.mat[6] + m1.mat[10] * m2.mat[10] + m1.mat[11] * m2.mat[14], m1.mat[8] * m2.mat[3] + m1.mat[9] * m2.mat[7] + m1.mat[10] * m2.mat[11] + m1.mat[11] * m2.mat[15],
	m1.mat[12] * m2.mat[0] + m1.mat[13] * m2.mat[4] + m1.mat[14] * m2.mat[8] + m1.mat[15] * m2.mat[12], m1.mat[12] * m2.mat[1] + m1.mat[13] * m2.mat[5] + m1.mat[14] * m2.mat[9] + m1.mat[15] * m2.mat[13], m1.mat[12] * m2.mat[2] + m1.mat[13] * m2.mat[6] + m1.mat[14] * m2.mat[10] + m1.mat[15] * m2.mat[14], m1.mat[12] * m2.mat[3] + m1.mat[13] * m2.mat[7] + m1.mat[14] * m2.mat[11] + m1.mat[15] * m2.mat[15]
	};


	return res;
}

struct vec4_float mat4_by_vec4(struct mat4_float m, struct vec4_float v) {
	struct vec4_float res = {
		m.mat[0] * v.x + m.mat[1] * v.y + m.mat[2] * v.z + m.mat[3] * v.w,
		m.mat[4] * v.x + m.mat[5] * v.y + m.mat[6] * v.z + m.mat[7] * v.w,
		m.mat[8] * v.x + m.mat[9] * v.y + m.mat[10] * v.z + m.mat[11] * v.w,
		m.mat[12] * v.x + m.mat[13] * v.y + m.mat[14] * v.z + m.mat[15] * v.w
	};
	return res;
}