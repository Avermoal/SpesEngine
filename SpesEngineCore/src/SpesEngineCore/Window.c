#include "SpesEngineCore/Window.h"

#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SpesEngineCore/Log.h"
#include "SpesEngineCore/ShaderProgram.h"
#include "SpesEngineCore/Events.h"
#include "SpesEngineCore/EventsData.h"
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


void window_init(struct Window *window, unsigned int width, unsigned int height, const char* title)
{
	if (!glfwInit()) {
		LOG_INFO("GLFW not init");
	}
	if (window) {
		window->pWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	}
	else {
		LOG_INFO("[ERROR] Memmory allocation failed, window don't create");
		glfwTerminate();
	}

	if (!window->pWindow) {
		LOG_INFO("[WINDOW]: Window don't create\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window->pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG_INFO("GLAD not init");
		window_terminate(window);
	}

	window->winData.width = width;
	window->winData.height = height;
	window->winData.title = title;

	glfwSetWindowUserPointer(window->pWindow, &window->winData);
	
	size_t vertex_shader_length = shader_length("../../res/main.glslv");
	size_t fragment_shader_length = shader_length("../../res/main.glslf");
	char* vertex_shader_src = calloc(vertex_shader_length, sizeof(char));
	char* fragment_shader_src = calloc(fragment_shader_length, sizeof(char));

	if (!load_shader("../../res/main.glslv", vertex_shader_src, vertex_shader_length)) {
		window_terminate(window);
	}
	if (!load_shader("../../res/main.glslf", fragment_shader_src, fragment_shader_length)) {
		window_terminate(window);
	}
	
	struct ShaderProgram sh_p = createShaderProgram(vertex_shader_src, fragment_shader_src);
	free(vertex_shader_src);
	free(fragment_shader_src);

	switch (sh_p.shader_compile_status) {
	case SHADER_PROGRAM_NOT_CREATED:
		LOG_INFO("[SHADER PROGRAM] Shader program don't create\n");
		window_terminate(window);
	case FAIL_TO_COMPILE_VERTEX_SHADER:
		LOG_INFO("[SHADER PROGRAM] Vertex shader don't compiled\n");
		window_terminate(window);
	case FAIL_TO_COMPILE_FRAGMENT_SHADER:
		LOG_INFO("[SHADER PROGRAM] Fragment shader don't compiled\n");
		window_terminate(window);
	}

	window->shader_program_id = sh_p.id;


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
	camera_init(&window->camera, vecPos, 70.f);
}

void window_terminate(struct Window *window)
{
	destroyShaderProgram(window->shader_program_id);
	glfwDestroyWindow(window->pWindow);
	glfwTerminate();
}

void on_update(struct Window *window)
{

	glClear(GL_COLOR_BUFFER_BIT);


	struct mat4_float projection = perspective(window->camera.fov, ((float)window->winData.width / (float)window->winData.height), 0.1f, 1000.f);
	struct mat4_float view = LookAt(window->camera.cameraPos, plus(window->camera.cameraPos,window->camera.cameraFront), window->camera.cameraUp);

	bindShaderProgram(window->shader_program_id);
	uniformMatrix("model", model, window->shader_program_id);
	uniformMatrix("view", view, window->shader_program_id);
	uniformMatrix("projection", projection, window->shader_program_id);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	if (jpressed(GLFW_KEY_TAB)) {
		toogleCursor(window->pWindow);
	}
	if (jclicked(GLFW_MOUSE_BUTTON_1)) {
		glClearColor(0.2f, 0.1f, 0.5f, 1.f);
	}
	if (jclicked(GLFW_MOUSE_BUTTON_2)) {
		glClearColor(0.4f, 0.7f, 0.2f, 1.f);
	}
	if (pressed(GLFW_KEY_W)) {
		window->camera.cameraPos = plus(window->camera.cameraPos, mult_by_numb(window->camera.cameraFront, 0.001f));
	}
	if (pressed(GLFW_KEY_S)) {
		window->camera.cameraPos = minus(window->camera.cameraPos, mult_by_numb(window->camera.cameraFront, 0.001f));
	}
	if (pressed(GLFW_KEY_D)) {
		window->camera.cameraPos = plus(window->camera.cameraPos, mult_by_numb(window->camera.cameraRight, 0.001f));
	}
	if (pressed(GLFW_KEY_A)) {
		window->camera.cameraPos = minus(window->camera.cameraPos, mult_by_numb(window->camera.cameraRight, 0.001f));
	}

	if (eventsData.cursor_locked) {
		LOG_INFO("cursor is lokced\n");
	}

	glfwSwapBuffers(window->pWindow);
	pullEvents();
}

void setCursorMode(GLFWwindow *pWindow, int mode)
{
	glfwSetInputMode(pWindow, GLFW_CURSOR, mode);
}
