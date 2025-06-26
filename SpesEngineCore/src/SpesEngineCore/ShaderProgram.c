#include "SpesEngineCore/ShaderProgram.h"

#include <stdio.h>

#include "SpesEngineCore/Log.h"

#include "Mathemathics/mat4_float.h"
#include "Mathemathics/some_func.h"

int load_shader(const char* relative_path, char* shader, size_t shader_length)
{
	FILE* shader_src = fopen(relative_path, "r");

	if (!shader_src) {
		LOG_INFO("[SHADER] Shader file: %s \t %s", relative_path, " don't open\n");
		return 0;
	}

	fread(shader, sizeof(char), shader_length, shader_src);

	fclose(shader_src);
	return 1;
}

struct ShaderProgram createShaderProgram(const char* vertex_shader, const char* fragment_shader)
{
	struct ShaderProgram sh_p;
	
	GLuint vertexShaderID, fragmentShaderID;
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShaderID, 1, &vertex_shader, NULL);
	glCompileShader(vertexShaderID);

	glShaderSource(fragmentShaderID, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShaderID);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		LOG_INFO("[ERROR] Vertex shader not compiled\n");
		sh_p.id = 0;
		sh_p.shader_compile_status = FAIL_TO_COMPILE_VERTEX_SHADER;
		return sh_p;
	}
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		LOG_INFO("[ERROR] Fragment shader not compiled\n");
		sh_p.id = 0;
		sh_p.shader_compile_status = FAIL_TO_COMPILE_FRAGMENT_SHADER;
		return sh_p;
	}

	sh_p.id = glCreateProgram();

	glAttachShader(sh_p.id, vertexShaderID);
	glAttachShader(sh_p.id, fragmentShaderID);
	glLinkProgram(sh_p.id);

	glDetachShader(sh_p.id, vertexShaderID);
	glDetachShader(sh_p.id, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glGetProgramiv(sh_p.id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(sh_p.id, 512, NULL, infoLog);
		LOG_INFO("[ERROR] shader program not created\n");
		sh_p.shader_compile_status = SHADER_PROGRAM_NOT_CREATED;
	}

	sh_p.shader_compile_status = SUCCESS;
	return sh_p;
}

void destroyShaderProgram(GLuint id)
{
	glDeleteShader(id);
}

void bindShaderProgram(GLuint id)
{
	glUseProgram(id);
}
void unbindShderProgram()
{
	glUseProgram(0);
}

size_t shader_length(const char* relative_path)
{
	FILE* shader = fopen(relative_path, "r");
	
	fseek(shader, 0L, SEEK_END);
	size_t size = ftell(shader);
	rewind(shader);
	fclose(shader);

	return size;
}


void uniformMatrix(const char* name, struct mat4_float matrix, GLuint shader_program_id)
{
	GLuint loc = glGetUniformLocation(shader_program_id, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat4_float_value_ptr(matrix));
}
