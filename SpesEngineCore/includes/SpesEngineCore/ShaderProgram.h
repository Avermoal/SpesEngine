#ifndef INCLUDES_SPES_ENGINE_CORE_SHADERPROGRAM_H
#define INCLUDES_SPES_ENGINE_CORE_SHADERPROGRAM_H

#include <glad/glad.h>

struct mat4_float;

struct ShaderProgram {
	GLuint id;
	enum SHADER_COMPILE_STATUS {
		SUCCESS,
		FAIL_TO_COMPILE_VERTEX_SHADER,
		FAIL_TO_COMPILE_FRAGMENT_SHADER,
		SHADER_PROGRAM_NOT_CREATED
	} shader_compile_status;
};

int load_shader(const char* relative_path, char* shader, size_t shader_length);

struct ShaderProgram createShaderProgram(const char* vertex_shader, const char* fragment_shader);
void destroyShaderProgram(GLuint id);

void bindShaderProgram(GLuint id);
void unbindShderProgram();

size_t shader_length(const char* relative_path);

void uniformMatrix(const char* name, struct mat4_float matrix, GLuint shader_program_id);


#endif//INCLUDES_SPES_ENGINE_CORE_SHADERPROGRAM_H
