#ifndef INCLUDES_MATHEMATHICS_SOME_FUNC_H
#define INCLUDES_MATHEMATHICS_SOME_FUNC_H

struct mat4_float;
struct vec3_float;

struct mat4_float LookAt(struct vec3_float eye, struct vec3_float center, struct vec3_float up);

struct mat4_float perspective(float fov, float aspectRatio, float near, float far);

struct mat4_float rotate(struct mat4_float model, float degree, struct vec3_float axis);

struct mat4_float translate(struct mat4_float mat, struct vec3_float vec);

struct mat4_float transpose(struct mat4_float mat);

void* mat4_float_value_ptr(struct mat4_float mat);

#endif//INCLUDES_MATHEMATHICS_SOME_FUNC_H