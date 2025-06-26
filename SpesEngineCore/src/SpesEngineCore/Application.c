#include "SpesEngineCore/Application.h"

#include "SpesEngineCore/Log.h"
#include "SpesEngineCore/Window.h"
#include "SpesEngineCore/Events.h"

enum APP_EXIT_CODE start_app()
{
	struct Window window;

  window_init(&window, 500, 500, "Test Spes Engine");
	if (!window.pWindow) {
		LOG_INFO("Window don't created\n");
		return CRITICAL;
	}

	events_system_init(window.pWindow);

	window.winData.window_should_not_close = true;

	while (window.winData.window_should_not_close) {
		on_update(&window);
	}
}
