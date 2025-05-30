#include "SpesEngineCore/Window.h"

#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SpesEngineCore/Log.h"
#include "SpesEngineCore/ShaderProgram.h"
#include "SpesEngineCore/Events.h"

GLfloat point[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5, -0.5f, 0.0f
};

GLfloat colors[] = {
1.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 1.0f
};

GLuint vao;


struct Window* window_init(unsigned int width, unsigned int height, const char* title) {
	struct Window* pWindow = malloc(sizeof(struct Window));
	if (!glfwInit()) {
		LOG_INFO("GLFW not init");
		return NULL;
	}
	if (pWindow) {
		pWindow->pWindow_ = glfwCreateWindow(width, height, title, NULL, NULL);
	}
	else {
		LOG_INFO("[ERROR] Memmory allocation failed, window don't create");
		glfwTerminate();
		return NULL;
	}

	if (!pWindow->pWindow_) {
		LOG_INFO("[WINDOW]: Window don't create\n");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(pWindow->pWindow_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG_INFO("GLAD not init");
		window_terminate(pWindow);
		return NULL;
	}

	pWindow->winData_.width_ = width;
	pWindow->winData_.height_ = height;
	pWindow->winData_.title_ = title;

	glfwSetWindowUserPointer(pWindow->pWindow_, &pWindow->winData_);
	
	size_t vertex_shader_length = shader_length("../../res/main.glslv");
	size_t fragment_shader_length = shader_length("../../res/main.glslf");
	char* vertex_shader_src = calloc(vertex_shader_length, sizeof(char));
	char* fragment_shader_src = calloc(fragment_shader_length, sizeof(char));

	if (!load_shader("../../res/main.glslv", vertex_shader_src, vertex_shader_length)) {
		window_terminate(pWindow);
		return NULL;
	}
	if (!load_shader("../../res/main.glslf", fragment_shader_src, fragment_shader_length)) {
		window_terminate(pWindow);
		return NULL;
	}
	
	struct ShaderProgram sh_p = createShaderProgram(vertex_shader_src, fragment_shader_src);
	free(vertex_shader_src);
	free(fragment_shader_src);

	switch (sh_p.shader_compile_status_) {
	case SHADER_PROGRAM_NOT_CREATED:
		LOG_INFO("[SHADER PROGRAM] Shader program don't create\n");
		window_terminate(pWindow);
		return NULL;
	case FAIL_TO_COMPILE_VERTEX_SHADER:
		LOG_INFO("[SHADER PROGRAM] Vertex shader don't compiled\n");
		window_terminate(pWindow);
		return NULL;
	case FAIL_TO_COMPILE_FRAGMENT_SHADER:
		LOG_INFO("[SHADER PROGRAM] Fragment shader don't compiled\n");
		window_terminate(pWindow);
		return NULL;
	}

	pWindow->shader_program_id_ = sh_p.id_;


	GLuint points_vbo = 0;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);



	glViewport(0, 0, width, height);
	return pWindow;
}

void window_terminate(struct Window* window) {
	glfwDestroyWindow(window->pWindow_);
	glfwTerminate();
	free(window);
	window = NULL;
}

void on_update(struct Window* window) {
	///glClearColor(0.3f, 0.7f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	bindShaderProgram(window->shader_program_id_);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	if (jpressed(GLFW_KEY_TAB)) {
		toogleCursor(window->pWindow_);
	}
	if (jclicked(GLFW_MOUSE_BUTTON_1)) {
		glClearColor(0.2f, 0.1f, 0.5f, 1.f);
	}

	glfwSwapBuffers(window->pWindow_);
	pullEvents();
}

void setCursorMode(GLFWwindow* pWindow, int mode) {
	glfwSetInputMode(pWindow, GLFW_CURSOR, mode);
}