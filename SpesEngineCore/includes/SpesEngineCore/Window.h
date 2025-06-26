#ifndef INCLUDES_SPES_ENGINE_CORE_WINDOW_H
#define INCLUDES_SPES_ENGINE_CORE_WINDOW_H

#include <stdbool.h>

#include "SpesEngineCore/Camera.h"

struct GLFWwindow;


struct windowData {
	unsigned int width, height;
	const char* title;
	bool window_should_not_close;
};

struct Window {
	struct GLFWwindow *pWindow;
	struct Camera camera;
	struct windowData winData;
	unsigned int shader_program_id;
};

void window_init(struct Window *window, unsigned int width, unsigned int height, const char *title);

void window_terminate(struct Window *window);

void on_update(struct Window *window);

void setCursorMode(struct GLFWwindow *pWindow, int mode);

#endif//INCLUDES_SPES_ENGINE_CORE_WINDOW_H
