#ifndef INCLUDES_SPES_ENGINE_CORE_APPLICATION_H
#define INCLUDES_SPES_ENGINE_CORE_APPLICATION_H

#include <stdbool.h>

struct Window;

struct Application {
	struct Window* pWindow_;
	bool app_should_not_close_;
};

enum APP_EXIT_CODE {
	EXIT_SUCCESS = 0,
	FAILURE,
	CRITICAL
};

enum APP_EXIT_CODE start_app();


#endif//INCLUDES_SPES_ENGINE_CORE_APPLICATION_H