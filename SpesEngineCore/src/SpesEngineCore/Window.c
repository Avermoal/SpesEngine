#include "SpesEngineCore/Window.h"

#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SpesEngineCore/Log.h"
#include "SpesEngineCore/ShaderProgram.h"
#include "SpesEngineCore/Events.h"
#include "SpesEngineCore/Camera.h"

#include "Mathemathics/mat4_float.h"
#include "Mathemathics/vec3_float.h"
#include "Mathemathics/some_func.h"

GLfloat point[] = {
	0.0f, 1.f, -2.0f,
	1.f, -1.f, -2.0f,
	-1.f, -1.f, -2.0f
};

GLfloat colors[] = {
1.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 1.0f
};

struct mat4_float model = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
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

	struct vec3_float vecPos = { 0.f, 0.f, 3.f };
	pWindow->camera_ = camera_init(vecPos, 90);

	return pWindow;
}

void window_terminate(struct Window* window) {
	camera_destroy(window->camera_);
	destroyShaderProgram(window->shader_program_id_);
	glfwDestroyWindow(window->pWindow_);
	glfwTerminate();
	free(window);
	window = NULL;
}

void on_update(struct Window* window) {

	glClear(GL_COLOR_BUFFER_BIT);


	struct mat4_float projection = perspective(window->camera_->fov_, ((float)window->winData_.width_ / (float)window->winData_.height_), 0.1f, 1000.f);
	struct mat4_float view = LookAt(window->camera_->cameraPos_, plus(window->camera_->cameraPos_,window->camera_->cameraFront_), window->camera_->cameraUp_);
	bindShaderProgram(window->shader_program_id_);
	uniformMatrix("model", model, window->shader_program_id_);
	uniformMatrix("view", view, window->shader_program_id_);
	uniformMatrix("projection", projection, window->shader_program_id_);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	if (jpressed(GLFW_KEY_TAB)) {
		toogleCursor(window->pWindow_);
	}
	if (jclicked(GLFW_MOUSE_BUTTON_1)) {
		glClearColor(0.2f, 0.1f, 0.5f, 1.f);
	}
	if (jclicked(GLFW_MOUSE_BUTTON_2)) {
		glClearColor(0.4f, 0.7f, 0.2f, 1.f);
	}
	if (pressed(GLFW_KEY_W)) {
		window->camera_->cameraPos_ = plus(window->camera_->cameraPos_, mult_by_numb(window->camera_->cameraFront_, 0.01f));
	}
	if (pressed(GLFW_KEY_S)) {
		window->camera_->cameraPos_ = minus(window->camera_->cameraPos_, mult_by_numb(window->camera_->cameraFront_, 0.01f));
	}
	if (pressed(GLFW_KEY_D)) {
		window->camera_->cameraPos_ = plus(window->camera_->cameraPos_, mult_by_numb(window->camera_->cameraRight_, 0.01f));
	}
	if (pressed(GLFW_KEY_A)) {
		window->camera_->cameraPos_ = minus(window->camera_->cameraPos_, mult_by_numb(window->camera_->cameraRight_, 0.01f));
	}

	glfwSwapBuffers(window->pWindow_);
	pullEvents();
}

void setCursorMode(GLFWwindow* pWindow, int mode) {
	glfwSetInputMode(pWindow, GLFW_CURSOR, mode);
}