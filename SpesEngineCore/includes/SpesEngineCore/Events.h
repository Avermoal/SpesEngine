#ifndef INCLUDES_SPES_ENGINE_CORE_EVENTS_H
#define INCLUDES_SPES_ENGINE_CORE_EVENTS_H

#include <stdbool.h>

struct GLFWwindow;

void events_system_init(struct GLFWwindow* pWindow);

void events_system_terminate();

void pullEvents();

void window_size_callback(struct GLFWwindow* pWindow, int width, int height);

void window_close_callback(struct GLFWwindow* pWindow);

void cursor_position_callback(struct GLFWwindow* pWindow, double xpos, double ypos);

void mouse_button_callback(struct GLFWwindow* pWindow, int button, int action, int mode);

void key_callback(struct GLFWwindow* pWindow, int key, int scancode, int action, int mode);

bool pressed(int keycode);
bool jpressed(int keycode);

bool clicked(int button);
bool jclicked(int button);

void toogleCursor(struct GLFWwindow* pWindow);


#endif//INCLUDES_SPES_ENGINE_CORE_EVENTS_H