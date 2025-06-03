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