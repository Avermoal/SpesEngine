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

void events_system_init(struct GLFWwindow* pWindow) {
	eventsData.current_ = 0;
	eventsData.deltaX_ = 0.f;
	eventsData.deltaY_ = 0.f;
	eventsData.x_ = 0.f;
	eventsData.y_ = 0.f;
	eventsData.cursor_locked_ = false;
	eventsData.cursor_started_ = false;

	eventsData.keys_ = calloc(MAX_KEYS_NUMBER, sizeof(bool));
	eventsData.frames_ = calloc(MAX_KEYS_NUMBER, sizeof(unsigned short));

	if (eventsData.keys_ == NULL || eventsData.frames_ == NULL) {
		LOG_INFO("[EVENT SYSTEM ERROR] Can not allocate memmory\n");
		return;
	}

	glfwSetWindowSizeCallback(pWindow, window_size_callback);
	glfwSetWindowCloseCallback(pWindow, window_close_callback);
	glfwSetMouseButtonCallback(pWindow, mouse_button_callback);
	glfwSetKeyCallback(pWindow, key_callback);
	glfwSetCursorPosCallback(pWindow, cursor_position_callback);
}

void events_system_terminate() {
	free(eventsData.keys_);
	free(eventsData.frames_);
	eventsData.keys_ = NULL;
	eventsData.frames_ = NULL;
}

void pullEvents() {
	++eventsData.current_;
	LOG_INFO("%d\n", eventsData.current_);
	eventsData.deltaX_ = 0.f;
	eventsData.deltaY_ = 0.f;
	glfwPollEvents();
}

void window_size_callback(struct GLFWwindow* pWindow, int width, int height) {
	glViewport(0, 0, width, height);

	struct windowData* winData = (struct windowData*)glfwGetWindowUserPointer(pWindow);
	winData->width_ = width;
	winData->height_ = height;
}

void window_close_callback(struct GLFWwindow* pWindow) {
	struct windowData* winData = (struct windowData*)glfwGetWindowUserPointer(pWindow);
	winData->window_should_not_close_ = false;
}

void cursor_position_callback(struct GLFWwindow* window, double xpos, double ypos) {
	if (eventsData.cursor_locked_) {
		eventsData.deltaX_ += xpos - eventsData.x_;
		eventsData.deltaY_ += ypos - eventsData.y_;
	}
	else {
		eventsData.cursor_started_ = true;
	}
	eventsData.x_ = xpos;
	eventsData.y_ = ypos;
}

void mouse_button_callback(struct GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) {
		eventsData.keys_[button + MOUSE_BUTTONS] = true;
		eventsData.frames_[button + MOUSE_BUTTONS] = eventsData.current_;
	}
	else if (action == GLFW_RELEASE) {
		eventsData.keys_[button + MOUSE_BUTTONS] = false;
		eventsData.frames_[button + MOUSE_BUTTONS] = eventsData.current_;
	}
}

void key_callback(struct GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		eventsData.keys_[key] = true;
		eventsData.frames_[key] = eventsData.current_;
	}
	else if (action == GLFW_RELEASE) {
		eventsData.keys_[key] = false;
		eventsData.frames_[key] = eventsData.current_;
	}
}

bool pressed(int keycode) {
	if (keycode < 0 || keycode >= MOUSE_BUTTONS) {
		return false;
	}
	return eventsData.keys_[keycode];
}

bool jpressed(int keycode) {
	if (keycode < 0 || keycode >= MOUSE_BUTTONS) {
		return false;
	}
	return eventsData.keys_[keycode] && (eventsData.frames_[keycode] == eventsData.current_);
}

bool clicked(int button) {
	if (button < 0 || (button + MOUSE_BUTTONS) >= MAX_KEYS_NUMBER) {
		return false;
	}
	return eventsData.keys_[button + MOUSE_BUTTONS];
}

bool jclicked(int button) {
	if (button < 0 || (button + MOUSE_BUTTONS) >= MAX_KEYS_NUMBER) {
		return false;
	}
	return eventsData.keys_[button + MOUSE_BUTTONS] && (eventsData.frames_[button + MOUSE_BUTTONS] == eventsData.current_);
}

void toogleCursor(struct GLFWwindow* pWindow) {
	eventsData.cursor_locked_ = !eventsData.cursor_locked_;
	setCursorMode(pWindow, eventsData.cursor_locked_ ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}