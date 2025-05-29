#ifndef INCLUDES_SPES_ENGINE_CORE_WINDOW_H
#define INCLUDES_SPES_ENGINE_CORE_WINDOW_H

struct GLFWwindow;

struct Window {
	struct GLFWwindow* pWindow_;
	unsigned int width_, height_;
	const char* title_;
	unsigned int shader_program_id_;
};

struct Window* window_init(unsigned int width, unsigned int height, const char* title);

void window_terminate(struct Window* window);

void on_update(struct Window* window);

#endif//INCLUDES_SPES_ENGINE_CORE_WINDOW_H