#ifndef INCLUDES_SPES_ENGINE_CORE_WINDOW_H
#define INCLUDES_SPES_ENGINE_CORE_WINDOW_H

#include <stdbool.h>

struct GLFWwindow;
struct Camera;

struct windowData {
	unsigned int width_, height_;
	const char* title_;
	bool window_should_not_close_;

};

struct Window {
	struct GLFWwindow* pWindow_;
	struct Camera* camera_;
	struct windowData winData_;
	unsigned int shader_program_id_;
};

struct Window* window_init(unsigned int width, unsigned int height, const char* title);

void window_terminate(struct Window* window);

void on_update(struct Window* window);

void setCursorMode(struct GLFWwindow* pWindow, int mode);

#endif//INCLUDES_SPES_ENGINE_CORE_WINDOW_H