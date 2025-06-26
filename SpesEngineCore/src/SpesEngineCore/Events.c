#include "SpesEngineCore/Events.h"

#include <string.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SpesEngineCore/Window.h"
#include "SpesEngineCore/EventsData.h"
#include "SpesEngineCore/Log.h"


#define MOUSE_BUTTONS 1024
#define MAX_KEYS_NUMBER 1032

void events_system_init(struct GLFWwindow* pWindow)
{
	eventsData.current = 0;
	eventsData.deltaX = 0.f;
	eventsData.deltaY = 0.f;
	eventsData.x = 0.f;
	eventsData.y = 0.f;
	eventsData.cursor_locked = false;
	eventsData.cursor_started = false;

	eventsData.keys = calloc(MAX_KEYS_NUMBER, sizeof(bool));
	eventsData.frames = calloc(MAX_KEYS_NUMBER, sizeof(unsigned short));

	if (eventsData.keys == NULL || eventsData.frames == NULL) {
		LOG_INFO("[EVENT SYSTEM ERROR] Can not allocate memmory\n");
		return;
	}

	glfwSetWindowSizeCallback(pWindow, window_size_callback);
	glfwSetWindowCloseCallback(pWindow, window_close_callback);
	glfwSetMouseButtonCallback(pWindow, mouse_button_callback);
	glfwSetKeyCallback(pWindow, key_callback);
	glfwSetCursorPosCallback(pWindow, cursor_position_callback);
}

void events_system_terminate()
{
	free(eventsData.keys);
	free(eventsData.frames);
	eventsData.keys = NULL;
	eventsData.frames = NULL;
}

void pullEvents()
{
	++eventsData.current;
	eventsData.deltaX = 0.f;
	eventsData.deltaY = 0.f;
	glfwPollEvents();
}

void window_size_callback(struct GLFWwindow* pWindow, int width, int height) {
	glViewport(0, 0, width, height);

	struct windowData* winData = (struct windowData*)glfwGetWindowUserPointer(pWindow);
	winData->width = width;
	winData->height = height;
}

void window_close_callback(struct GLFWwindow* pWindow)
{
	struct windowData* winData = (struct windowData*)glfwGetWindowUserPointer(pWindow);
	winData->window_should_not_close = false;
}

void cursor_position_callback(struct GLFWwindow* window, double xpos, double ypos)
{
	if (eventsData.cursor_locked) {
		eventsData.deltaX += xpos - eventsData.x;
		eventsData.deltaY += ypos - eventsData.y;
	}
	else {
		eventsData.cursor_started = true;
	}
	eventsData.x = xpos;
	eventsData.y = ypos;
}

void mouse_button_callback(struct GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) {
		eventsData.keys[button + MOUSE_BUTTONS] = true;
		eventsData.frames[button + MOUSE_BUTTONS] = eventsData.current;
	}
	else if (action == GLFW_RELEASE) {
		eventsData.keys[button + MOUSE_BUTTONS] = false;
		eventsData.frames[button + MOUSE_BUTTONS] = eventsData.current;
	}
}

void key_callback(struct GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS) {
		eventsData.keys[key] = true;
		eventsData.frames[key] = eventsData.current;
	}
	else if (action == GLFW_RELEASE) {
		eventsData.keys[key] = false;
		eventsData.frames[key] = eventsData.current;
	}
}

bool pressed(int keycode)
{
	if (keycode < 0 || keycode >= MOUSE_BUTTONS) {
		return false;
	}
	return eventsData.keys[keycode];
}

bool jpressed(int keycode)
{
	if (keycode < 0 || keycode >= MOUSE_BUTTONS) {
		return false;
	}
	return eventsData.keys[keycode] && (eventsData.frames[keycode] == eventsData.current);
}

bool clicked(int button)
{
	if (button < 0 || (button + MOUSE_BUTTONS) >= MAX_KEYS_NUMBER) {
		return false;
	}
	return eventsData.keys[button + MOUSE_BUTTONS];
}

bool jclicked(int button)
{
	if (button < 0 || (button + MOUSE_BUTTONS) >= MAX_KEYS_NUMBER) {
		return false;
	}
	return eventsData.keys[button + MOUSE_BUTTONS] && (eventsData.frames[button + MOUSE_BUTTONS] == eventsData.current);
}

void toogleCursor(struct GLFWwindow* pWindow)
{
	eventsData.cursor_locked = !eventsData.cursor_locked;
	setCursorMode(pWindow, eventsData.cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}
