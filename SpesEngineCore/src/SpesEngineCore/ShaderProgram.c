#include "SpesEngineCore/ShaderProgram.h"

#include <stdio.h>

#include "SpesEngineCore/Log.h"

int load_shader(const char* relative_path, char* shader, size_t shader_length) {
	FILE* shader_src = fopen(relative_path, "r");

	if (!shader_src) {
		LOG_INFO("[SHADER] Shader file: %s \t %s", relative_path, " don't open\n");
		return 0;
	}

	fread(shader, sizeof(char), shader_length, shader_src);

	fclose(shader_src);
	return 1;
}

struct ShaderProgram createShaderProgram(const char* vertex_shader, const char* fragment_shader) {
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
		sh_p.id_ = 0;
		sh_p.shader_compile_status_ = FAIL_TO_COMPILE_VERTEX_SHADER;
		return sh_p;
	}
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		LOG_INFO("[ERROR] Fragment shader not compiled\n");
		sh_p.id_ = 0;
		sh_p.shader_compile_status_ = FAIL_TO_COMPILE_FRAGMENT_SHADER;
		return sh_p;
	}

	sh_p.id_ = glCreateProgram();

	glAttachShader(sh_p.id_, vertexShaderID);
	glAttachShader(sh_p.id_, fragmentShaderID);
	glLinkProgram(sh_p.id_);

	glDetachShader(sh_p.id_, vertexShaderID);
	glDetachShader(sh_p.id_, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glGetProgramiv(sh_p.id_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(sh_p.id_, 512, NULL, infoLog);
		LOG_INFO("[ERROR] shader program not created\n");
		sh_p.shader_compile_status_ = SHADER_PROGRAM_NOT_CREATED;
	}

	sh_p.shader_compile_status_ = SUCCESS;
	return sh_p;
}

void bindShaderProgram(GLuint id) {
	glUseProgram(id);
}
void unbindShderProgram() {
	glUseProgram(0);
}

size_t shader_length(const char* relative_path) {
	FILE* shader = fopen(relative_path, "r");
	
	fseek(shader, 0L, SEEK_END);
	size_t size = ftell(shader);
	rewind(shader);
	fclose(shader);

	return size;
}