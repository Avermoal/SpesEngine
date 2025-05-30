#include "SpesEngineCore/Application.h"

#include "SpesEngineCore/Log.h"
#include "SpesEngineCore/Window.h"
#include "SpesEngineCore/Events.h"

enum APP_EXIT_CODE start_app() {
	struct Window* pWindow = window_init(500, 500, "Test Spes Engine");
	if (!pWindow) {
		LOG_INFO("Window don't created\n");
		return CRITICAL;
	}

	events_system_init(pWindow->pWindow_);

	pWindow->winData_.window_should_not_close_ = true;

	while (pWindow->winData_.window_should_not_close_) {
		on_update(pWindow);
	}
	free(pWindow);
	pWindow = NULL;
}