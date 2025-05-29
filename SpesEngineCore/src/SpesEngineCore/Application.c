#include "SpesEngineCore/Application.h"

#include "SpesEngineCore/Log.h"
#include "SpesEngineCore/Window.h"

enum APP_EXIT_CODE start_app() {
	struct Application app;
	app.pWindow_ = window_init(500, 500, "Test Spes Engine");
	if (!app.pWindow_) {
		LOG_INFO("Window don't created\n");
		return CRITICAL;
	}
	app.app_should_not_close_ = true;

	while (app.app_should_not_close_) {
		on_update(app.pWindow_);
	}
}